//
// Created by bayk on 04.11.2021.
//

#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdint>
#include <iostream>

#include "RSA.h"

size_t exp_mod(size_t number, size_t degree, size_t module) {
    size_t result = 1;
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

bool is_prime(const size_t& number){
    return exp_mod(2, number - 1, number) == 1;
}

uint64_t RSA::generate_prime_number(){
    std::srand(std::time(nullptr));
    std::this_thread::sleep_for(std::chrono::milliseconds (1000));
    size_t result = (std::rand() % 2147483675) + 2147483675;
    while (!is_prime(result)){
        ++result;
    }
    return result;
}

size_t nod(size_t first, size_t second){
    while (first != 0 && second != 0)
        if (first > second)
            first %= second;
        else
            second %= first;
    return first + second;
}

size_t RSA::generate_exponent(){
    size_t result = std::rand() % 1073741824 + 1073741824;
    size_t second = (p - 1) * (q - 1);
    while (nod(result, second) != 1){
        ++result;
    }
    return result;
}


//Расширенный алгоритм Евклида
size_t nod_ex(size_t a, size_t b, size_t &x, size_t &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    size_t x1, y1;
    size_t d = nod_ex(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

//Обратное по модулю
size_t inverse_modulo(size_t number, size_t module) {
    size_t x, y;
    nod_ex(number, module, x, y);
    x = (x + module) % module;
    return x;
}

size_t RSA::generate_secret_exponent() {
    size_t a = (p - 1) * (q - 1);
    return inverse_modulo(e, a);
}
