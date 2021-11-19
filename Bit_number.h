//
// Created by bayk on 13.11.2021.
//

#ifndef COURSE_PROJECT_BIT_NUMBER_H
#define COURSE_PROJECT_BIT_NUMBER_H

#include <bitset>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stack>

/*
 * Так как в стандартных библиотеках с++ нет инструментов для работы с длинной арифметикой я реализовал свой класс
 * для решения этой задачи
 */

template <const size_t size>
class Bit_number {
    static int get_nearest_10_degree(size_t number);
public:
    std::bitset<size> _data;
    uint32_t get_32_bit_int();
    Bit_number();
    explicit Bit_number(const std::bitset<size>& other);
    Bit_number(size_t number);
    Bit_number(const std::string& number);
    void print_bin();
    std::string get_hex();
    void read_hex(const std::string& hex_number);
    bool operator[](const size_t& position);
    Bit_number<size>& operator=(size_t number); // почему то не ссрабатывает этот оператор
    Bit_number<size> operator+(Bit_number<size>& number);
    Bit_number<size> operator+(int number);
    Bit_number<size> &operator++();
    Bit_number<size>& operator+=(Bit_number<size> number);
    Bit_number<size>& operator+=(const std::bitset<size>& number);
    Bit_number<size>& operator+=(const size_t& number);
    Bit_number<size> operator-(Bit_number<size> number);
    Bit_number<size> operator-(int number);
    Bit_number<size>& operator-=(Bit_number<size>& number);
    Bit_number<size>& operator-=(const size_t& number);
    Bit_number<size> operator*(Bit_number<size> number);
    Bit_number<size>& operator*=(Bit_number<size>& number);
    Bit_number<size> &operator~();
    Bit_number<size> operator/(Bit_number<size> number);
    Bit_number<size>& operator/=(Bit_number<size> number);
    Bit_number<size> operator%(Bit_number<size> number);
    Bit_number<size>& operator%=(Bit_number<size> number);
    Bit_number<size> operator<<(const size_t& number);
    Bit_number<size> &operator<<=(const size_t& number);
    Bit_number<size> operator>>(const size_t& number);
    Bit_number<size> &operator>>=(const size_t& number);
    bool operator!=(Bit_number<size>& rhs);
    bool operator==(Bit_number<size>& rhs);
    bool operator<=(Bit_number<size>& rhs);
    bool operator<(Bit_number<size>& rhs);
    bool operator>=(Bit_number<size>& rhs);
    bool operator>(Bit_number<size>& rhs);
    bool operator!=(const size_t& rhs);
    bool operator==(const size_t& rhs);
    bool operator<=(const size_t& rhs);
    bool operator<(const size_t& rhs);
    bool operator>=(const size_t& rhs);
    bool operator>(const size_t& rhs);
    void get_random();
    void get_random_half();
    void get_random_quarter();
    // пришлось поместить реализация оператора вывода так как были ошибки компиляции
    friend std::ostream& operator<<(std::ostream& stream, Bit_number number){
        Bit_number<size> zero;
        Bit_number<size> base;
        uint32_t max = (zero - 1).get_32_bit_int();
        int degree = get_nearest_10_degree(max);
        max = static_cast<uint32_t>(std::pow(10, degree));
        uint32_t billion = 1000000000;
        base = std::min(billion, max);
        degree = std::min(degree, 9);
        std::stack<uint32_t> stack;
        while (number != zero){
            uint32_t temp = (number % base).get_32_bit_int();
            stack.push(temp);
            number /= base;
        }
        while (!stack.empty()){
            stream << stack.top();
            stack.pop();
            stream << std::setw(degree) << std::setfill('0');
        }
        stream << std::setw(0);
        return stream;
    }
};

#endif //COURSE_PROJECT_BIT_NUMBER_H
