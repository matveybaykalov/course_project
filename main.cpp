#include <iostream>
#include "Keccak.h"
#include "RSA.h"

int main() {
//    std::string test;
//    int b = 130;
//    test += static_cast<char>(b);
//    char c = static_cast<char>((test[0] ^ 130) + 65);
//    Keccak a("a");
//    a.print_hash();
//    RSA a(39901, 42979, 1714905079, 63949, 406683349);
    RSA a;
    std::cout << "p = " << a.p << "\nq = " << a.q << "\nn = " << a.n << "\ne = " << a.e << "\nd = " << a.d << '\n';
    std::string filename = "asd";
    std::string data = "Hello, world! This is a simple text for test";
    std::cout << data.length() << '\n';
    a.encode(data, filename);
    return 0;
}
