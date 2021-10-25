#include <iostream>
#include "Keccak.h"

int main() {
//    std::string test;
//    int b = 130;
//    test += static_cast<char>(b);
//    char c = static_cast<char>((test[0] ^ 130) + 65);
    Keccak a("a");
    a.print_hash();
    return 0;
}
