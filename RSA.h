//
// Created by bayk on 04.11.2021.
//

#ifndef COURSE_PROJECT_RSA_H
#define COURSE_PROJECT_RSA_H

#include <cstdio>
#include "string"

class RSA {
    size_t generate_prime_number();
    size_t generate_exponent();
    size_t generate_secret_exponent();
public:
    size_t p, q, n, e, d;
    RSA();
    RSA(const size_t& p,const size_t& q,const size_t& n,const size_t& e,const size_t& d): p(p), q(q), n(n), e(e), d(d){};
    void encode(std::string& text, std::string& filename);
};


#endif //COURSE_PROJECT_RSA_H
