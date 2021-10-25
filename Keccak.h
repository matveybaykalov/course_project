//
// Created by bayk on 09.10.2021.
//

#ifndef COURSE_PROJECT_KECCAK_H
#define COURSE_PROJECT_KECCAK_H

#include <string>
#include <iostream>
#include <vector>

class Keccak {
    const size_t r = 1088, c = 512; // эти переменные необходимо будет поменять для разного формата хеша
    size_t rounds_number = 0, w = 0;
    std::vector<std::vector<std::string>> s;
    std::vector<std::string> blocks;
    std::string z; // полученный хеш
    std::string message;
    void padding(const std::string &input);
    size_t count_rounds_number();
    void adding_blocks();
    [[nodiscard]] std::vector<std::vector<std::string>> from_string_to_matrix(const std::string& s) const;
    void absorbing();
    void squeezing();
    std::vector<std::vector<std::string>> absorbing_round(std::vector<std::vector<std::string>>& A, const std::string& rc_constant);
    std::vector<std::vector<std::string>> permutation_function(std::vector<std::vector<std::string>>& str);
    [[nodiscard]] std::string RC(const size_t& t) const;
public:
    explicit Keccak(const std::string& input);
    void print_message(){
        std::cout << message << '\n';
    }
    void print_hash(){
        std::cout << z << '\n';
    }
};

#endif //COURSE_PROJECT_KECCAK_H
