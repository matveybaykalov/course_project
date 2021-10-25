//
// Created by bayk on 09.10.2021.
//

#include "Keccak.h"
#include <bitset>
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>

std::vector<std::vector<std::string>> operator^(const std::vector<std::vector<std::string>>& lhs,
                                                const std::vector<std::vector<std::string>>& rhs){
    size_t W = lhs[0][0].length();
    std::vector<std::vector<std::string>> result(5, std::vector<std::string>(5));
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < W; ++k) {
                result[i][j] += static_cast<char>(lhs[i][j][k] ^ rhs[i][j][k]);
            }
        }
    }
    return result;
}

std::string operator^(const std::string& lhs, const std::string& rhs){
    std::string result;
    result.clear(); // Странная строчка, надо подумать... скорее всего удалить...
    for (int i = 0; i < rhs.length(); ++i) {
        result += static_cast<char>(lhs[i] ^ rhs[i]);
    }
    return result;
}

std::string operator&&(const std::string& lhs, const std::string& rhs){
    std::string result;
    for (int i = 0; i < rhs.length(); ++i) {
        result += static_cast<char>(lhs[i] & rhs[i]);
    }
    return result;
}

std::string from_string_to_hex(const std::string& str){
    std::string result;
    for (const char& x : str) {
        std::stringstream ss;
        std::string temp;
        ss << std::setw(2) << std::setfill('0') << std::hex << (static_cast<int>(x) + 256) % 256;
        ss >> temp;
        result += temp;
    }
    return result;
}

void Keccak::absorbing() {
    for (const auto& x : blocks) {
        s = s ^ from_string_to_matrix(x);
        s = permutation_function(s);
    }
}

std::string get_hex_for_answer(const std::string& str){
    std::string result;
    std::string temp;
    for(const char& x : str){
        size_t temp_f = ((static_cast<int>(x) + 256) % 256) >> 4;
        size_t temp_s = ((static_cast<int>(x) + 256) % 256) & 15;
        std::stringstream ss2, ss1;
        ss2 << std::setw(1) << std::setfill('0') << std::hex << (temp_s);
        std::string second, first;
        ss2 >> second;
        ss1 << std::setw(1) << std::setfill('0') << std::hex << (temp_f);
        ss1 >> first;
        temp = first + second;
    }
    result = temp + result;
    return result;
}

void Keccak::squeezing() {
    do{
        for (int j = 0; j < 5; ++j) {
            for (int i = 0; i < 5; ++i) {
                if((5 * j + i) < c / (2 * w)){
                    z += get_hex_for_answer(s[i][j]);
                }
            }
        }
        s = permutation_function(s);
    } while (z.length() < c / 8);
}

Keccak::Keccak(const std::string &input) { //надо подумать, почему выводит неправильный размер хеша и сделать полную проверку на правильность выполнения
    rounds_number = count_rounds_number();
    padding(input);
    adding_blocks();
    absorbing();
    squeezing();
}

bool rc (const size_t& t){
    if(t % 255 == 0)
        return true;
    std::bitset<9> R("000000001");
    for (int i = 0; i < t % 255; ++i) {
        R <<= 1;
        R[0] = R[0] ^ R[8];
        R[4] = R[4] ^ R[8];
        R[5] = R[5] ^ R[8];
        R[6] = R[6] ^ R[8];
    }
    return R[0];
}

std::string from_bool_vector_to_string(std::vector<bool>& str){
    std::string result;
    for (int i = 0; i < str.size() / 8; ++i) {
        int symbol = 0;
        for (int j = 7; j >= 0; --j) {
            symbol <<= 1;
            symbol += str[i * 8 + j];
        }
        result.insert(0, 1, static_cast<char>(symbol));
    }
    return result;
}

std::vector<bool> from_string_to_bool_vector(const std::string& str){
    size_t length = str.length();
    std::vector<bool> result(length * 8, false);
    for (int i = 0; i < length; ++i) { // перевожу строку в набор бит
        std::bitset<8> byte((static_cast<int>(str[i]) + 256) % 256);
        for (int j = 0; j < 8; ++j) {
            result[(length - i - 1) * 8 + j] = byte[j];
        }
    }
    return result;
}

std::string Keccak::RC (const size_t& t) const{
    std::vector<bool>result(w, false);
    auto l = static_cast<size_t>(log2(static_cast<double>(w)));
    for (int i = 0; i <= l; ++i) {
//        bool a = rc(i + 7 * t); // rc(7)=0 rc(8)=1 rc(9)=0 rc(10)=1 rc(11)=1 rc(12)=0 rc(13)=0
        result[(1<<i)-1] = rc(i + 7 * t); // res[0]=0 res[1]=1 res[3]=0 res[7]=1 res[15]=1 res[31]=0 res[63]=0
    }
    return from_bool_vector_to_string(result);
}

std::string cyclic_shift(const std::string& str, const size_t& n){ // циклический сдвиг вправо
    size_t length = str.length();
    std::vector<bool> result(length * 8, false);
    std::vector<bool> str_bits(length * 8, false);
    str_bits = from_string_to_bool_vector(str);
    for (int i = 0; i < length * 8; ++i) {
//        std::cout << (str.length() * 8 - n + i) % (length * 8) << '\n';
        result[i] = str_bits[(str.length() * 8 - n + i) % (length * 8)]; // НЕПРАВИЛЬНО пример для одного байта: 7->5, 6->4, 5->3, 4->2, 3->1, 2->0, 1->7, 0->6
    }
    return from_bool_vector_to_string(result);
}

size_t shift_size(const int& x, const int& y){
    if(x == 0 && y == 0){
        return 0;
    }
    size_t w = 64; // надо бы брать эту величину из поля класса
    int i = 1, j = 0, t = 0, j_temp;
    while (i != x || j != y){
        j_temp = j;
        j = (2 * i + 3 * j) % 5;
        i = j_temp;
        ++t;
    }
    return static_cast<size_t>(((t + 1) * (t + 2) / 2) % w);
}

std::string string_not(const std::string& str){ // функция инвертирует биты в строке
    std::vector<bool>result (str.length() * 8, false);
    result = from_string_to_bool_vector(str);
    for (int i = 0; i < str.length() * 8; ++i) {
        result[i] = !result[i];
    }
    return from_bool_vector_to_string(result);
}

std::vector<std::vector<std::string>> Keccak::absorbing_round(std::vector<std::vector<std::string>> &A,
                                                              const std::string &rc_constant) {
//    theta step
    std::vector<std::string> C(5), D(5);
    std::vector<std::vector<std::string>> B(5, std::vector<std::string>(5));
    for (int i = 0; i < 5; ++i) {
        C[i] = A[0][i] ^ A[1][i] ^ A[2][i] ^ A[3][i] ^ A[4][i]; // сложение по модулю 2 каждой строки матрицы
    }
    for (int i = 0; i < 5; ++i) {
//        std::string temp = cyclic_shift("PRW", 2);
        D[i] = C[((i - 1) + 5) % 5] ^ cyclic_shift(C[(i + 1) % 5], 1); // можно написать получше, но так понятно
    }
//    for (int i = 0; i < 5; ++i) {
//        std::cout << from_string_to_hex(D[i]) << ' ';
//    }
//    std::cout << '\n';
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 5; ++i) {
            A[i][j] = A[i][j] ^ D[j];
        }
    }
//    ro and pi step
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 5; ++i) {
            B[(2 * i + 3 * j) % 5][j] = cyclic_shift(A[j][i], shift_size(i, j));
        }
    }
//    chi step
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 5; ++i) {
            A[i][j] = B[i][j] ^ (string_not(B[(i + 1) % 5][j]) && B[(i + 2) % 5][j]);
        }
    }
//    iota step
    A[0][0] = A[0][0] ^ rc_constant;
//    for (int j = 0; j < 5; ++j) {
//        for (int i = 0; i < 5; ++i) {
//            std::cout << from_string_to_hex(A[i][j]) << ' ';
//        }
//        std::cout << '\n';
//    }
//    std::cout << '\n';
    return A;
}

std::vector<std::vector<std::string>> Keccak::permutation_function(std::vector<std::vector<std::string>>& str) {
    for (size_t i = 0; i < rounds_number; ++i) { // надо учитывать, что char это знаковый тип, но считает правильно
        str = absorbing_round(str, RC(i));
//        std::string temp = RC(i);
//        std::cout << std::setw(2) << std::dec << i << ' ';
//        for (char a : temp) { // пример для вывода полученных чисел, 256 %256 надо, чтобы получить из отрицательных положительные
//            std::cout << std::setw(2) << std::setfill('0') << std::hex << (static_cast<int>(a) + 256) % 256;
//        }
//        std::cout << '\n';
    }
    return str;
}

void Keccak::padding(const std::string &input) {
    s.resize(5, std::vector<std::string>(5)); //инициализация строки состояния
    for(int i = 0; i < 5; ++i){
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 8; ++k) {
                s[i][j] += '\x00';
            }
        }
    }
    const size_t remains =  (r / 8) - (input.length() % (r / 8));
    std::string addition;
    for (int i = 0; i < remains - 1; ++i) {
        addition += '\x00';
    }
    addition += '\x80';
    addition[0] ^= '\x01';
    message = input + addition;
}

size_t Keccak::count_rounds_number() {
    size_t b = r + c;
    auto l = static_cast<size_t>(log2(static_cast<double>(b) / 25));
    w = static_cast<size_t>(static_cast<double>(b) / 25);
    return 12 + 2 * l;
}

void Keccak::adding_blocks() {
    for (int i = 0; i < message.length() / (r / 8); ++i) {
        blocks.push_back(message.substr(i * r, r));
    }
}

std::vector<std::vector<std::string>> Keccak::from_string_to_matrix(const std::string& str) const{
    std::vector<std::vector<std::string>> result (5, std::vector<std::string>(5));
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 5; ++i) {
            if ((5 * j + i) * w < r)
                for (const char& x : str.substr((5 * j + i) * (w / 8), w / 8)){
                    result[i][j] = x + result[i][j];
                }
//            result[i][j] = str.substr((5 * j + i) * (w / 8), w / 8);
        }
    }
    return result;
}
