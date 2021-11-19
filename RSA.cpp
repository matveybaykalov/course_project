//
// Created by bayk on 04.11.2021.
//

#include "RSA.h"

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <future>
#include <thread>
#include <utility>
#include <vector>

// инициализация переменных для шифрования
void RSA::generate(){
    std::srand(std::time(nullptr));
    p = generate_prime_number();
    q = generate_prime_number();
    while (q == p){
        q = generate_prime_number();
    }
    n = p * q;
    e = generate_exponent();
    d = generate_secret_exponent();
}

//функция возведения числа по модулю
Bit_number<size> exp_mod(Bit_number<size> number, Bit_number<size> degree, Bit_number<size> module){
    Bit_number<size> result = 1;
    while (degree != 0) {
        if (degree[0] == 1) {
            result *= number;
            result %= module;
        }
        number *= number;
        number %= module;
        degree >>= 1;
    }
    return result;
}

//проверка на простоту по малой теореме Ферма
std::pair<bool, Bit_number<size>> is_prime(Bit_number<size> number){
    return {exp_mod(2, number - 1, number) == 1, number};
}

int RSA::get_threads_count() const {
    return threads_count;
}
 //создание простого числа
Bit_number<size> RSA::generate_prime_number(Bit_number<size> number, const bool& is_revers) const{
    Bit_number<size> result;
    bool flag = false; // этот флаг отвечает за то, найдено ли простое число
    if (number == 0){
        number.get_random_quarter();
    }
    number._data[0] = true;
    std::vector<std::future<std::pair<bool, Bit_number<size>>>> threads(threads_count - 1);
    while (!flag){
        for (int j = 1; j < threads_count; ++j) {
            threads[j - 1] = std::async(is_prime, number);
            if (is_revers)
                number -= 2;
            else
                number += 2;
        }
        std::pair<bool, Bit_number<size>> temp = is_prime(number);
        if (temp.first){
            flag = true;
            result = temp.second;
        }
        number += 2;
        for (int j = 1; j < threads_count; ++j) {
            temp = threads[j - 1].get();
            if (temp.first){
                flag = true;
                result = temp.second;
            }
        }
    }
    return result;
}

// быстрый алгоритм Евклида
Bit_number<size> nod(Bit_number<size> first, Bit_number<size> second){
    while (first != 0 && second != 0){
        if (first > second)
            first %= second;
        else
            second %= first;
    }
    return first + second;
}

Bit_number<size> RSA::generate_exponent(){
    Bit_number<size> result;
    Bit_number<size> f = (p - 1) * (q - 1);
    result = generate_prime_number(f, true);
    while (nod(result, f) != 1){
        result -= 2;
        result = generate_prime_number(result, true);
    }
    return result;
}


//Расширенный алгоритм Евклида
Bit_number<size> nod_ex(Bit_number<size> a, Bit_number<size> b, Bit_number<size> &x, Bit_number<size> &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    Bit_number<size> x1, y1;
    Bit_number<size> d = nod_ex(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

//Обратное по модулю
Bit_number<size> inverse_modulo(Bit_number<size> number, Bit_number<size> module) {
    Bit_number<size> x, y;
    nod_ex(number, module, x, y);
    x = (x + module) % module;
    return x;
}

Bit_number<size> RSA::generate_secret_exponent() {
    Bit_number<size> a = (p - 1) * (q - 1);
    return inverse_modulo(e, a);
}

std::string get_string_from_ciphertext(Bit_number<size>& ciphertext, RSA& object){
    uint32_t block = (exp_mod(ciphertext, object.d, object.n)).get_32_bit_int();
    std::string result;
    for (size_t j = 0; j < object.block_size; ++j) {
        result += static_cast<char>((block << (8 * j)) >> (8 * (object.block_size - 1)));
    }
    return result;
}

std::string RSA::encode(std::string text) {
    if (e == 0 || n == 0){
        throw std::logic_error("Empty e or n");
    }
    std::string result;
    // количество символов, которые необходимо добавить в конец текста, чтобы разделить его на блоки
    size_t pad = (block_size - text.length() % block_size) % block_size;
    for (int i = 0; i < pad; ++i) { // дополнение текста нулями, до длины кратноой длине блока
        text += '\x00';
    }
    std::vector<uint32_t> text_in_numbers;
    for (size_t i = 0; i < static_cast<size_t>(text.length() / block_size); ++i) {
        uint32_t block = 0;
        for (size_t j = 0; j < block_size; ++j) {
            block <<= 8;
            block += text[i * block_size + j];
        }
        text_in_numbers.push_back(block);
    }
    // реализация многопоточности
    std::vector<std::future<Bit_number<size>>> number_threads(threads_count - 1);
    std::vector<Bit_number<size>> ciphertext(text_in_numbers.size());
    for (int i = 0; i < std::ceil(static_cast<double> (text_in_numbers.size()) / threads_count); ++i) {
        for (int j = 1; j < threads_count; ++j){
            if (i * threads_count + j < text_in_numbers.size()){
                number_threads[j - 1] = std::async(exp_mod, text_in_numbers[i * threads_count + j], e, n);
            }
        }
        ciphertext[i * threads_count] = exp_mod(text_in_numbers[i * threads_count], e, n);
        for (int j = 1; j < threads_count; ++j){
            if (i * threads_count + j < text_in_numbers.size()){
                ciphertext[i * threads_count + j] = number_threads[j - 1].get();
            }
        }
    }
    for (auto &x : ciphertext){
        result += x.get_hex();
    }
    return result;
}

std::string RSA::decode(const std::string &text) { // будем ситать, что проверка на существование файлов выполнена в интерфейсе программы
    if (d == 0 || n == 0){
        throw std::logic_error("Empty d or n");
    }
    std::string result;
    std::vector<Bit_number<size>> ciphertext(text.length() / (size / 8));
    for (int i = 0; i < text.length() / (size / 8); ++i) {
        ciphertext[i].read_hex(text.substr(i * (size / 8), (size / 8)));
    }
    // так как расшифровку каждого блока можно рассматривать как самостоятельную задачу, значит их можно выполнить
    // в нескольких потоках
    std::vector<std::future<std::string>> string_threads(threads_count - 1);
    for (int i = 0; i < std::ceil(static_cast<double> (ciphertext.size()) / threads_count); ++i) { // расшифрование работает правильно во n потоках
        for (int j = 1; j < threads_count; ++j) {
            if (i * threads_count + j < ciphertext.size()){
                string_threads[j - 1] = std::async(get_string_from_ciphertext, std::ref(ciphertext[i * threads_count + j]), std::ref(*this));
            }
        }
        result += get_string_from_ciphertext(ciphertext[i * threads_count], *this);
        for (int j = 1; j < threads_count; ++j){
            if (i * threads_count + j < ciphertext.size()){
                result += string_threads[j - 1].get();
            }
        }
    }
    while (result[result.length() - 1] == '\x00'){
        result.erase(result.length() - 1, 1);
    }
    return result;
}

std::pair<std::string, std::string> RSA::get_public_key() {
    return {e.get_hex(), n.get_hex()};
}

std::pair<std::string, std::string> RSA::get_private_key() {
    return {d.get_hex(), n.get_hex()};
}

void RSA::set_public_key(const std::string &hex_e, const std::string &hex_n) {
    e.read_hex(hex_e);
    n.read_hex(hex_n);
}

void RSA::set_private_key(const std::string &hex_d, const std::string &hex_n) {
    d.read_hex(hex_d);
    n.read_hex(hex_n);
}
