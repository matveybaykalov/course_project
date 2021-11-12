//
// Created by bayk on 04.11.2021.
//

#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#include "RSA.h"

RSA::RSA() {
    p = generate_prime_number();
    q = generate_prime_number();
    n = p * q;
    e = generate_exponent();
    d = generate_secret_exponent();
}

uint64_t exp_mod(uint64_t number, uint64_t degree, uint64_t module) {
    uint64_t result = 1;
    while (degree) {
        if (degree & 1) {
            result *= number;
            result %= module;
        }
        number *= number;
        number %= module;
        degree >>= 1;
    }
    return result;
}

bool is_prime(const uint64_t& number){
    return exp_mod(2, number - 1, number) == 1;
}

uint64_t RSA::generate_prime_number(){
    std::srand(std::time(nullptr));
    std::this_thread::sleep_for(std::chrono::milliseconds (1000));
    uint64_t result = (std::rand() % 32768) + 32768;
    while (!is_prime(result)){
        ++result;
    }
    return result;
}

uint64_t nod(uint64_t first, uint64_t second){
    while (first != 0 && second != 0)
        if (first > second)
            first %= second;
        else
            second %= first;
    return first + second;
}

uint64_t RSA::generate_exponent(){
    uint64_t result = std::rand() % 32768 + 32768;
    uint64_t second = (p - 1) * (q - 1);
    while (!is_prime(result) && nod(result, second) != 1){
        ++result;
    }
    return result;
}


//Расширенный алгоритм Евклида
uint64_t nod_ex(uint64_t a, uint64_t b, uint64_t &x, uint64_t &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    uint64_t x1, y1;
    uint64_t d = nod_ex(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

//Обратное по модулю
uint64_t inverse_modulo(uint64_t number, uint64_t module) {
    uint64_t x, y;
    nod_ex(number, module, x, y);
    x = (x + module) % module;
    return x;
}

uint64_t RSA::generate_secret_exponent() {
    uint64_t a = (p - 1) * (q - 1);
    return inverse_modulo(e, a);
}

void RSA::encode(std::string &text, std::string &filename) {
    size_t block_size = 2;
    size_t pad = (block_size - text.length() % block_size) % block_size; // количество символов, которые необходимо добавить в конец текста, чтобы разделить его на блоки
    for (int i = 0; i < pad; ++i) {
        text += '\x00';
    }
    std::vector<uint16_t> text_in_numbers;
    for (size_t i = 0; i < static_cast<size_t>(text.length() / block_size); ++i) {
        uint16_t block = 0;
        for (size_t j = 0; j < block_size; ++j) {
            block <<= 8;
            block += text[i * block_size + j];
        }
        text_in_numbers.push_back(block);
    }
    std::vector<uint64_t> ciphertext(text_in_numbers.size());
    for (size_t i = 0; i < text_in_numbers.size(); ++i) {
        ciphertext[i] = exp_mod(text_in_numbers[i], e, n);
//        std::cout << ciphertext[i] << ' ';
    }
//    std::cout << '\n';
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        uint16_t block = exp_mod(ciphertext[i], d, n);
//        std::cout << block << '\n';
        std::string str;
        for (size_t j = 0; j < block_size; ++j) {
            str += static_cast<char>((block << (8 * j)) >> (8 * (block_size - 1)));
        }
        std::cout << str;
    }
//    std::cout << "\np = " << p << "\nq = " << q << "\nn = " << n << "\ne = " << e << "\nd = " << d << '\n';
    std::cout << "\n" << p << ", " << q << ", " << n << ", " << e << ", " << d << '\n';
}
