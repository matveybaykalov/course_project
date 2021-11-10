//
// Created by bayk on 04.11.2021.
//

#ifndef COURSE_PROJECT_RSA_H
#define COURSE_PROJECT_RSA_H

#include <cstdio>

class RSA {
    size_t generate_prime_number();
    size_t generate_exponent();
    size_t generate_secret_exponent();
public:
    size_t p = generate_prime_number();
    size_t q = generate_prime_number();
    size_t n = p * q;
    size_t e = generate_exponent();
    size_t d = generate_secret_exponent();
};


#endif //COURSE_PROJECT_RSA_H
