//
// Created by bayk on 13.11.2021.
//

#include "Bit_number.h"
#include <iostream>
#include <stdexcept>
#include <stack>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <sstream>

template <const size_t size>
Bit_number<size>::Bit_number(size_t number) {
    size_t i = 0;
    while (number && i != size){
        if (number & 1){
            _data[i] = 1;
        }
        number >>= 1;
        ++i;
    }
}

//template <const size_t size>
//Bit_number<size> &Bit_number<size>::operator=(const Bit_number<size> &other) {
//    _data = other._data;
//    return *this;
//}

template <const size_t size>
void Bit_number<size>::print_bin() {
    for (size_t i = size - 1; i >= 0 && i < size; --i) {
        std::cout << _data[i];
    }
    std::cout << '\n';
}

template <const size_t size>
std::string Bit_number<size>::get_hex() {
    std::string result;
    std::stringstream ss;
    int i = size / 2 - 1;
    while (i >= 0) {
        int number = 0;
        int degree = 1;
        for (int j = 3; j >= 0; --j) {
            if (_data[i - j]){
                number += degree;
            }
            degree <<= 1;
        }
        i -= 4;
        ss << std::hex << number;
    }
    ss >> result;
    return result;
}

template <const size_t size>
void set_hex_in_bits(Bit_number<size>& number, int hex, const int& position){
//    std::cout << hex << ' ' << position << '\n';
    for (int j = 0; j < 4; ++j){
        number._data[position + j] = hex % 2;
        hex >>= 1;
    }
}

template <const size_t size>
void Bit_number<size>::read_hex(const std::string &hex_number) {
    for (int i = size / 2; i < size; ++i) {
        _data[i] = 0;
    }
    for (int i = 0; i < size / 8; ++i) {
//        std::cout << hex_number[hex_number.length() - 1 - i] << '\n';
        switch (hex_number[hex_number.length() - 1 - i]) {
            case '0': {
                set_hex_in_bits(*this, 0, i * 4);
                break;
            }
            case '1': {
                set_hex_in_bits(*this, 1, i * 4);
                break;
            }
            case '2': {
                set_hex_in_bits(*this, 2, i * 4);
                break;
            }
            case '3': {
                set_hex_in_bits(*this, 3, i * 4);
                break;
            }
            case '4': {
                set_hex_in_bits(*this, 4, i * 4);
                break;
            }
            case '5': {
                set_hex_in_bits(*this, 5, i * 4);
                break;
            }
            case '6': {
                set_hex_in_bits(*this, 6, i * 4);
                break;
            }
            case '7': {
                set_hex_in_bits(*this, 7, i * 4);
                break;
            }
            case '8': {
                set_hex_in_bits(*this, 8, i * 4);
                break;
            }
            case '9': {
                set_hex_in_bits(*this, 9, i * 4);
                break;
            }
            case 'a': {
                set_hex_in_bits(*this, 10, i * 4);
                break;
            }
            case 'b': {
                set_hex_in_bits(*this, 11, i * 4);
                break;
            }
            case 'c': {
                set_hex_in_bits(*this, 12, i * 4);
                break;
            }
            case 'd': {
                set_hex_in_bits(*this, 13, i * 4);
                break;
            }
            case 'e': {
                set_hex_in_bits(*this, 14, i * 4);
                break;
            }
            case 'f': {
                set_hex_in_bits(*this, 15, i * 4);
                break;
            }
        }
    }
//    std::string number;
//    std::stringstream ss;
//    std::cout << hex_number << '\n';
//    ss << std::hex << hex_number;
//    ss >> number;
//    std::cout << number << '\n';
//    if (number.empty()){ // код такой же как и в конструкторе, который принимает на вход десятичное число в строковом формате
//        throw std::logic_error("empty number");
//    }
//    std::string number_copy = number;
//    std::reverse(number_copy.begin(), number_copy.end());
//    Bit_number<size> result;
//    Bit_number<size> billion(1000000000);
//    for (int i = std::floor(static_cast<double>(number_copy.length()) / 9); i >= 0 ; --i) {
//        std::string str_mob_billion = number_copy.substr(i * 9, 9);
//        std::reverse(str_mob_billion.begin(), str_mob_billion.end());
//        if (!str_mob_billion.empty()){
//            int mod_billion = std::stoi(str_mob_billion);
//            result = result * billion + mod_billion;
//        }
//    }
}

//std::string revers(const std::string& str){
//    std::string result;
//    for (size_t i = str.length() - 1; i >= 0 && i < str.length(); --i) {
//        result += str[i];
//    }
//    return result;
//}

template <const size_t size>
Bit_number<size>::Bit_number(const std::string &number) {
    if (number.empty()){
        throw std::logic_error("empty number");
    }
    std::string number_copy = number;
    std::reverse(number_copy.begin(), number_copy.end());
    Bit_number<size> result;
    Bit_number<size> billion(1000000000);
    for (int i = std::floor(static_cast<double>(number_copy.length()) / 9); i >= 0 ; --i) {
        std::string str_mob_billion = number_copy.substr(i * 9, 9);
        std::reverse(str_mob_billion.begin(), str_mob_billion.end());
        if (!str_mob_billion.empty()){
            int mod_billion = std::stoi(str_mob_billion);
            result = result * billion + mod_billion;
        }
    }
    _data = result._data;
}

template <const size_t size>
Bit_number<size>& Bit_number<size>::operator=(size_t number) {
    size_t i = 0;
    while (number && i != size){
        if (number & 1){
            _data[i] = 1;
        }
        number >>= 1;
        ++i;
    }
    return *this;
}

template <const size_t size>
Bit_number<size>::Bit_number() {
    _data = 0;
}

template <const size_t size>
Bit_number<size>::Bit_number(const std::bitset<size> &other) {
    _data = other;
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator+=(Bit_number<size> number) {
    *this = *this + number;
    return *this;
}

template <const size_t size>
Bit_number<size> Bit_number<size>::operator+(int number) {
    Bit_number<size> bit_number;
    bit_number = number;
    Bit_number<size> result;
    result = *this + bit_number;
    return result;
}

template <const size_t size>
Bit_number<size> Bit_number<size>::operator+(Bit_number<size>& number) {
    Bit_number<size> result;
    bool bit = false;
    bool next_bit;
    for (size_t i = 0; i < size; ++i) {
        if (_data[i] + number._data[i] + bit <= 1){
            next_bit = false;
        } else {
            next_bit = true;
        }
        result._data[i] = _data[i] ^ number._data[i] ^ bit;
        bit = next_bit;
    }
    return result;
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator+=(const std::bitset<size>& number) {
    bool bit = false;
    bool next_bit;
    for (size_t i = 0; i < size; ++i) {
        if (_data[i] + number[i] + bit <= 1){
            next_bit = false;
        } else {
            next_bit = true;
        }
        _data[i] = _data[i] ^ number[i] ^ bit;
        bit = next_bit;
    }
    return *this;
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator+=(const size_t &number) {
    *this += std::bitset<size>(number);
    return *this;
}

template <const size_t size>
Bit_number<size> Bit_number<size>::operator<<(const size_t &number) {
    return Bit_number<size>(_data << number);
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator<<=(const size_t &number) {
    _data <<= number;
    return *this;
}

template <const size_t size>
Bit_number<size> Bit_number<size>::operator>>(const size_t &number) {
    return Bit_number<size>(_data >> number);
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator>>=(const size_t &number) {
    _data >>= number;
    return *this;
}

template <const size_t size>
bool Bit_number<size>::operator[](const size_t &position) {
    if (position < size){
        return _data[position];
    } else {
        throw std::out_of_range("out of range");
    }
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator*=(Bit_number<size> &number) {
    Bit_number<size> result;
    size_t i = 0;
    while (i != size){
        if (number[i] == 1){
            result += _data << i;
        }
        ++i;
    }
    *this = result;
    return *this;
}

template <const size_t size>
Bit_number<size> Bit_number<size>::operator*(Bit_number<size> number) {
    Bit_number<size> result;
    size_t i = 0;
    while (i != size){
        if (number[i] == 1){
            result += _data << i;
        }
        ++i;
    }
    return result;
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator~() {
    for(size_t i = 0; i < size; ++i){
        _data[i] = _data[i] ^ 1;
    }
    return *this;
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator++() {
    *this += (std::bitset<size>(1));
    return *this;
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator-=(Bit_number<size>& number) {
    *this = *this - number;
    return *this;
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator-=(const size_t &number) {
    *this = *this - number;
    return *this;
}

template <const size_t size>
Bit_number<size> Bit_number<size>::operator-(int number) {
    Bit_number<size> bit_number = number;
    Bit_number<size> result;
    result = *this - bit_number;
    return result;
}

template <const size_t size>
Bit_number<size> Bit_number<size>::operator-(Bit_number<size> number) {
    Bit_number<size> result = *this;
    result += (std::bitset<size>(1));
    ~number;
    result += number;
    ~number;
    return result;
}


template <const size_t size>
size_t get_high_bit_position(Bit_number<size>& number){
    for (size_t i = size - 1; i >= 0 && i < size; --i) {
        if (number[i] == 1)
            return i;
    }
    return size;
}

template <const size_t size>
Bit_number<size> Bit_number<size>::operator/(Bit_number<size> number) {
    Bit_number<size> result;
    Bit_number<size> divisible = *this;
    if (get_high_bit_position<size>(number) == size) {
        throw std::logic_error("Division by zero");
    }
    size_t shifts;
    size_t divisible_high_bit = get_high_bit_position<size>(*this);
    size_t divider_high_bit = get_high_bit_position<size>(number);
    if (divider_high_bit > divisible_high_bit){
        return result;
    }
    shifts = 1 + divisible_high_bit - divider_high_bit;
    number <<= divisible_high_bit - divider_high_bit;
    while (shifts){
        result <<= 1;
        if (number <= divisible){
            result._data[0] = 1;
            divisible -= number;
        }
        number >>= 1;
        --shifts;
    }
    return result;
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator/=(Bit_number<size> number){
    *this = *this / number;
    return *this;
}

template <const size_t size>
Bit_number<size> Bit_number<size>::operator%(Bit_number<size> number) {
    Bit_number<size> result = *this;
    if (get_high_bit_position<size>(number) == size) {
        throw std::logic_error("Division by zero");
    }
    size_t shifts;
    size_t divisible_high_bit = get_high_bit_position<size>(*this);
    size_t divider_high_bit = get_high_bit_position<size>(number);
    if (divider_high_bit > divisible_high_bit){
        return result;
    }
    shifts = 1 + divisible_high_bit - divider_high_bit;
    number <<= divisible_high_bit - divider_high_bit;
    while (shifts){
        if (number <= result){
            result -= number;
        }
        number >>= 1;
        --shifts;
    }
    return result;
}

template <const size_t size>
Bit_number<size> &Bit_number<size>::operator%=(Bit_number<size> number){
    *this = *this % number;
    return *this;
}

template <const size_t size>
void Bit_number<size>::get_random() {
    for (int i = 0; i < size; ++i) {
        _data[i] = rand() % 2;
    }
    _data[size - 1] = true;
}

template <const size_t size>
void Bit_number<size>::get_random_half() {
    for (int i = 0; i < size / 2; ++i) {
        _data[i] = rand() % 2;
    }
    _data[size / 2 - 1] = true;
}

template <const size_t size>
void Bit_number<size>::get_random_quarter() {
    for (int i = 0; i < size / 4; ++i) {
        _data[i] = rand() % 2;
    }
    _data[size / 4 - 1] = true;
}

template <const size_t size>
bool Bit_number<size>::operator<(Bit_number<size>& rhs){
    for (size_t i = size - 1; i >= 0 && i < size ; --i) {
        if (_data[i] == rhs[i]){
            continue;
        } else {
            return _data[i] < rhs[i];
        }
    }
    return false;
}

template <const size_t size>
bool Bit_number<size>::operator<=(Bit_number<size>& rhs){
    for (size_t i = size - 1; i >= 0 && i < size ; --i) {
        if (_data[i] == rhs[i]){
            continue;
        } else {
            return _data[i] < rhs[i];
        }
    }
    return true;
}

template <const size_t size>
bool Bit_number<size>::operator>(Bit_number<size>& rhs){
    for (size_t i = size - 1; i >= 0 && i < size ; --i) {
        if (_data[i] == rhs[i]){
            continue;
        } else {
            return _data[i] > rhs[i];
        }
    }
    return false;
}

template <const size_t size>
bool Bit_number<size>::operator>=(Bit_number<size>& rhs){
    for (size_t i = size - 1; i >= 0 && i < size ; --i) {
        if (_data[i] == rhs[i]){
            continue;
        } else {
            return _data[i] > rhs[i];
        }
    }
    return true;
}

template <const size_t size>
bool Bit_number<size>::operator==(Bit_number<size>& rhs){
    for (size_t i = size - 1; i >= 0 && i < size ; --i) {
        if (_data[i] == rhs[i]){
            continue;
        } else {
            return false;
        }
    }
    return true;
}

template <const size_t size>
bool Bit_number<size>::operator!=(Bit_number<size>& rhs){
    for (size_t i = size - 1; i >= 0 && i < size ; --i) {
        if (_data[i] == rhs[i]){
            continue;
        } else {
            return true;
        }
    }
    return false;
}

template <const size_t size>
bool Bit_number<size>::operator<(const size_t &rhs) {
    Bit_number<size> temp(rhs);
    return *this < temp;
}

template <const size_t size>
bool Bit_number<size>::operator>(const size_t &rhs) {
    Bit_number<size> temp(rhs);
    return *this > temp;
}

template <const size_t size>
bool Bit_number<size>::operator<=(const size_t &rhs) {
    Bit_number<size> temp(rhs);
    return *this <= temp;
}

template <const size_t size>
bool Bit_number<size>::operator>=(const size_t &rhs) {
    Bit_number<size> temp(rhs);
    return *this >= temp;
}

template <const size_t size>
bool Bit_number<size>::operator==(const size_t &rhs) {
    return _data == rhs;
}

template <const size_t size>
bool Bit_number<size>::operator!=(const size_t &rhs) {
    return _data != rhs;
}

template <const size_t size>
uint32_t Bit_number<size>::get_32_bit_int(){
    uint32_t result = 0;
    uint32_t degree = 1;
    for (int i = 0; i < size && i < 32; ++i) {
        if (_data[i] == 1){
            result += degree;
        }
        degree <<= 1;
    }
    return result;
}

template <const size_t size>
int Bit_number<size>::get_nearest_10_degree(size_t number) {
    int counter = 0;
    while (number){
        number /= 10;
        ++counter;
    }
    return counter;
}

//template <const size_t size>
//std::ostream& operator<< (std::ostream& stream, Bit_number<size> number){
//    Bit_number<size> zero;
//    Bit_number<size> base;
//    uint32_t max = (zero - 1).get_32_bit_int();
//    int degree = number.get_nearest_10_degree(max);
//    max = static_cast<uint32_t>(std::pow(10, degree));
//    uint32_t billion = 1000000000;
//    base = std::min(billion, max);
//    degree = std::min(degree, 9);
//    std::stack<uint32_t> stack;
//    while (number != zero){
//        uint32_t temp = (number % base).get_32_bit_int();
//        stack.push(temp);
//        number /= base;
//    }
//    while (!stack.empty()){
//        stream << stack.top();
//        stack.pop();
//        stream << std::setw(degree) << std::setfill('0');
//    }
//    stream << std::setw(0);
//    return stream;
//}
//    // буду выводить числа по 1 000 000 000
//    Bit_number<size1> zero;
//    Bit_number<size1> billion = 1000000000;
//    std::stack<uint32_t> stack;
//    while (number != zero){
//        stack.push(get_32_bit_int(number % billion));
//        number /= billion;
//    }
//    while (!stack.empty()){
//        stream << stack.top();
//        stack.pop();
//        stream << std::setw(9) << std::setfill('0');
//    }
//    return stream;
//}
