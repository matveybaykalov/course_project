#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>

#include "Keccak.h"
#include "RSA.h"
#include "Bit_number.h"

int main() {
    /*
     * В RSA e и n являютня открытым ключом, но в ЭЦП наоборот. e, n - секретный ключ, d, n - открытый ключ
     */
    std::string ciphertext = "output.txt";
    std::string public_key = "public_key.txt";
    std::string secret_key = "secret_key.txt";
//    std::string data = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has sur";
    std::string data = "Hello, world! This is a simple text for test!";
    std::chrono::time_point<std::chrono::steady_clock> start, end;
//    std::vector<int> threads = {1, 2, 4, 6, 8, 12, 16, 24};
//    for (auto& x : threads){
//    start = std::chrono::steady_clock::now();
//    RSA a ("13537289423717485487", "14320178819959816561", "193856405285185166490811488608699750207", "17978637650425240913", "67042497404501136819590391440920256657");
    {
        std::string n, d, e;
        RSA a;
        a.generate();
        e = a.get_public_key().first;
        n = a.get_public_key().second;
        d = a.get_private_key().first;

        std::ofstream output; // нужно попробовать без вектора ciphertext
        output.open(ciphertext);
        output << a.encode(data);
        output.close();

        std::ofstream s_key;
        s_key.open(secret_key);
        s_key << e << n;
        s_key.close();

        std::ofstream p_key;
        p_key.open(public_key);
        p_key << d << n;
        p_key.close();
    }

    {
        RSA a;
        std::string n, d, temp, text;
        std::ifstream p_key;
        p_key.open(public_key);
        p_key >> temp;
        p_key.close();

        d = temp.substr(0,size / 8);
        n = temp.substr(size / 8,size / 8);
        a.set_private_key(d, n);

        std::ifstream input;
        input.open(ciphertext);
        input >> text;
        input.close();

        std::cout << a.decode(text) << '\n';
    }

//    end = std::chrono::steady_clock::now();
//    std::cout << "\nTime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms; Threads count = " << a.get_threads_count() << "\n";
//    std::cout << a.d << ' ' << a.n << '\n';
//    }
//    b.print_bin();
//    c.print_bin();
//    std::cout << "a = " << a << '\n';
//    std::cout << "b = " << b << '\n';
//    std::cout << "c = " << c << '\n';
    return 0;
}
