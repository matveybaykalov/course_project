//
// Created by bayk on 04.11.2021.
//

#ifndef COURSE_PROJECT_RSA_H
#define COURSE_PROJECT_RSA_H

#include "Bit_number.h"

#include <cstdio>
#include <string>
#include <thread>

const size_t size = 256;
Bit_number<size> exp_mod(Bit_number<size> number, Bit_number<size> degree, Bit_number<size> module);

class RSA {
    int threads_count = static_cast<int>(std::thread::hardware_concurrency());
    [[nodiscard]] Bit_number<size> generate_prime_number(Bit_number<size> number = 0, const bool &is_revers = false) const;
    Bit_number<size> generate_exponent();
    Bit_number<size> generate_secret_exponent();
public:
    size_t block_size = 4;
    Bit_number<size> p, q, n, e, d;
    [[nodiscard]] int get_threads_count() const;
    void generate();
    std::pair<std::string, std::string> get_public_key();
    std::pair<std::string, std::string> get_private_key();
    void set_public_key(const std::string &hex_e, const std::string &hex_n);
    void set_private_key(const std::string &hex_d, const std::string &hex_n);
    std::string decode(const std::string &text);
    std::string encode(std::string text);
};

#endif //COURSE_PROJECT_RSA_H
