//
// Created by bayk on 18.11.2021.
//

#include "Digital_signature.h"
#include "Keccak.h"
#include "RSA.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::string read_from_file(const std::string &path){
    /*
     * Эта функция считывает данные из файла. Минусом является то, что она работает только с фалами подобные txt.
     * Можно расширить функционал, считывая файлы в бинарном режиме, но тогда надо знать с какого момента в них
     * начинается текст, чтобы его хешировать
     */
    std::string result, temp;
    std::ifstream input;
    input.open(path);
    while (std::getline(input, temp)){
        result += temp;
    }
    input.close();
    return result;
}

Digital_signature::Digital_signature() {
    /*
     * Здесь представлена реализация интерфейса взаимодействия с пользователем для сохдания ЭЦП
     */
    std::cout << "Hello, what do you want to do?\n"
    << "1. sign the document\n"
    << "2. verify signature\n"
    << "3. get verify certificate\n"
    << "0. exit\n";
    int mode;
    while (std::cin >> mode){
        if (mode == 1){
            fs::path path_to_file;
            std::string path_to_file_string;
            std::cout << "Enter the path to file or 0 to exit\n";
            std::cin.ignore(1);
            while (std::getline(std::cin, path_to_file_string)){ // проверка корректности ввода
                try {
                    path_to_file = path_to_file_string;
                    if (path_to_file_string == "0"){
                        exit(0);
                    }
                    if (is_directory(path_to_file)){
                        throw std::logic_error(path_to_file.string() + " is a directory");
                    }
                    if (!exists(path_to_file)){
                        throw std::logic_error(path_to_file.string() + " is not exist");
                    }
                    break;
                } catch (std::exception &e) {
                    std::cout << e.what() << '\n';
                    std::cout << "Please, enter the path to file again\n";
                }
            }
            RSA rsa;
            std::ofstream output;

            std::cout << "Do you have a secret key?\n"
            << "1. yes\n"
            << "2. no\n"
            << "0. exit\n";
            int cert_mode;
            while (std::cin >> cert_mode){
                if (cert_mode == 1){
                    fs::path path_to_secret_key;
                    std::string path_to_secret_key_string;
                    std::cout << "Enter the path to secret key or 0 to exit\n";
                    std::cin.ignore(1);
                    while (std::getline(std::cin, path_to_secret_key_string)){ //проверка корректности ввода
                        try {
                            path_to_secret_key = path_to_secret_key_string;
                            if (path_to_secret_key == "0"){
                                exit(0);
                            }
                            if (is_directory(path_to_secret_key)){
                                throw std::logic_error(path_to_secret_key.string() + " is a directory");
                            }
                            if (!exists(path_to_secret_key)){
                                throw std::logic_error(path_to_secret_key.string() + " is not exist");
                            }
                            if (path_to_secret_key.filename().extension() != ".key"){
                                throw std::invalid_argument(path_to_secret_key.string() + " is not secret key");
                            }
                            break;
                        } catch (std::exception &e) {
                            std::cout << e.what() << '\n';
                            std::cout << "Please, enter the path to secret key again\n";
                        }
                    } // на этом этапе у меня есть путь до файла и секретного ключа
                    std::ifstream input; // считываение содержания секретного ключа
                    input.open(path_to_secret_key.string());
                    std::string secret_key;
                    input >> secret_key;
                    input.close();

                    try{
                        if (secret_key.length() != size / 8 * 2){
                            throw std::length_error("Incorrect secret key");
                        }
                        e = secret_key.substr(0, size / 8);
                        n = secret_key.substr(size / 8, size / 8);
                        break;
                    } catch (std::exception &e) {
                        std::cout << e.what() << '\n';
                    }
                } else if (cert_mode == 2){
                    std::cout << "Enter the path to the directory where the files will be saved\n"
                              << "Press enter to save to the program folder or 0 to exit\n";
                    std::string path_to_directory_string;
                    fs::path path_to_directory;
                    std::cin.ignore(1);
                    while (std::getline(std::cin, path_to_directory_string)){
                        try {
                            path_to_directory = path_to_directory_string;
                            if (path_to_directory == "0"){
                                exit(0);
                            }
                            if (path_to_directory_string.empty()){
                                path_to_directory = fs::current_path();
                            }
                            if (!is_directory(path_to_directory)){
                                throw std::logic_error(path_to_directory.string() + " is not a directory");
                            }
                            if (!exists(path_to_directory)){
                                throw std::logic_error(path_to_directory.string() + " is not exist");
                            }
                            break;
                        } catch (std::exception &e) {
                            std::cout << e.what() << '\n';
                            std::cout << "Please, enter the path to directory again\n";
                        }
                    }
                    std::cout << "Please wait, now we generate certificate for you...\n";
                    rsa.generate(); // инициализация переменных, необходимых для шифрования
                    e = rsa.get_public_key().first;
                    d = rsa.get_private_key().first;
                    n = rsa.get_public_key().second;

                    // создание всех необходимых фалов для пользователя, чтобы он мог подписывать документы
                    output.open(path_to_directory.string() + "/secret_key.key");
                    output << e << n;
                    output.close();

                    output.open(path_to_directory.string() + "/certificate.cert");
                    output << d << n;
                    output.close();

                    output.open(path_to_directory.string() + "/certificate_signature.sign");
                    Keccak cert_hash(read_from_file(path_to_directory.string() + "/certificate.cert"));
                    rsa.set_public_key(system_e, system_n);
                    output << rsa.encode(cert_hash.get_hash());
                    output.close();

                    std::cout << "The certificate has been successfully created! Don't tell anyone the secret key.\n";
                    break;
                } else if (cert_mode == 0){
                    exit(0);
                } else {
                    std::cout << "Unknown command, please, try again\n";
                }
                std::cout << "\nDo you have a secret key?\n"
                          << "1. yes\n"
                          << "2. no\n"
                          << "0. exit\n";
            }
            std::cout << "Please wait, now we generate signature...\n";
            rsa.set_public_key(e, n); // процесс шифрования хеша (создание подписи)
            Keccak hash(read_from_file(path_to_file_string));
            output.open(path_to_file.parent_path().string() + "/" + path_to_file.filename().stem().string() + ".sign");
            output << rsa.encode(hash.get_hash());
            output.close();
            std::cout << "Signature successfully created!\nIt is located in the folder with the source file.\n";
        } else if (mode == 2){
            fs::path path_to_file, path_to_signature, path_to_certificate;
            std::string path_to_file_string, path_to_signature_string, path_to_certificate_string;
            std::string certificate;
            std::cout << "Enter the path to file or 0 to exit\n";
            std::cin.ignore(1);
            while (std::getline(std::cin, path_to_file_string)){ //проверка корректности ввода
                try {
                    path_to_file = path_to_file_string;
                    if (path_to_file_string == "0"){
                        exit(0);
                    }
                    if (is_directory(path_to_file)){
                        throw std::logic_error(path_to_file.string() + " is a directory");
                    }
                    if (!exists(path_to_file)){
                        throw std::logic_error(path_to_file.string() + " is not exist");
                    }
                    break;
                } catch (std::exception &e) {
                    std::cout << e.what() << '\n';
                    std::cout << "Please, enter the path to file again\n";
                }
            }
            std::cout << "Enter the path to file signature or 0 to exit\n";
            while (std::getline(std::cin, path_to_signature_string)){
                try {
                    path_to_signature = path_to_signature_string;
                    if (path_to_signature_string == "0"){
                        exit(0);
                    }
                    if (is_directory(path_to_signature)){
                        throw std::logic_error(path_to_signature.string() + " is a directory");
                    }
                    if (!exists(path_to_signature)){
                        throw std::logic_error(path_to_signature.string() + " is not exist");
                    }
                    if (path_to_signature.filename().extension() != ".sign"){
                        throw std::invalid_argument(path_to_signature.string() + " is not file signature");
                    }
                    break;
                } catch (std::exception &e) {
                    std::cout << e.what() << '\n';
                    std::cout << "Please, enter the path to file signature again\n";
                }
            }
            std::cout << "Enter the path to certificate or 0 to exit\n";
            while (std::getline(std::cin, path_to_certificate_string)){
                try {
                    path_to_certificate = path_to_certificate_string;
                    if (path_to_certificate_string == "0"){
                        exit(0);
                    }
                    if (is_directory(path_to_certificate)){
                        throw std::logic_error(path_to_certificate.string() + " is a directory");
                    }
                    if (!exists(path_to_certificate)){
                        throw std::logic_error(path_to_certificate.string() + " is not exist");
                    }
                    if (path_to_certificate.filename().extension() != ".cert"){
                        throw std::invalid_argument(path_to_certificate.string() + " is not certificate");
                    }
                    certificate = read_from_file(path_to_certificate_string);
                    if (certificate.length() != size / 8 * 2){
                        throw std::invalid_argument("Incorrect certificate");
                    }
                    break;
                } catch (std::exception &e) {
                    std::cout << e.what() << '\n';
                    std::cout << "Please, enter the path to file signature again\n";
                }
            }
            std::cout << "Please wait...\n";
            RSA rsa;
            d = certificate.substr(0, size / 8);
            n = certificate.substr(size / 8, size / 8);
            rsa.set_private_key(d, n); // инициализация переменных, необходимых для расшифровыания
            std::string check_sum = rsa.decode(read_from_file(path_to_signature_string));
            Keccak hash(read_from_file(path_to_file_string));
            if (hash.get_hash() == check_sum){ // подпись верна если хеш документа равен расшифрованному хешу подписи
                std::cout << "Signature is correct!\n";
            } else {
                std::cout << "Signature is incorrect. Changes have been made to the document or incorrect signature!\n";
            }
        } else if (mode == 3){
            std::cout << "Enter the path to the directory where the files will be saved\n"
                      << "Press enter to save to the program folder or 0 to exit\n";
            std::string path_to_directory_string;
            fs::path path_to_directory;
            std::cin.ignore(1);
            while (std::getline(std::cin, path_to_directory_string)){
                try {
                    path_to_directory = path_to_directory_string;
                    if (path_to_directory == "0"){
                        exit(0);
                    }
                    if (path_to_directory_string.empty()){
                        path_to_directory = fs::current_path();
                    }
                    if (!is_directory(path_to_directory)){
                        throw std::logic_error(path_to_directory.string() + " is not a directory");
                    }
                    if (!exists(path_to_directory)){
                        throw std::logic_error(path_to_directory.string() + " is not exist");
                    }
                    break;
                } catch (std::exception &e) {
                    std::cout << e.what() << '\n';
                    std::cout << "Please, enter the path to directory again\n";
                }
            }
            std::ofstream output; // создание проверкочного сертификата, которым можно проверить корректность выданного сертификата
            output.open(path_to_directory.string() + "/verify_certificate.cert");
            output << system_d << system_n;
            output.close();
            std::cout << "Successfully!\n";
        } else if (mode == 0){
            exit(0);
        } else {
            std::cout << "Unknown command, please, try again\n";
        }
        std::cout << "\nWhat do you want to do?\n"
                  << "1. sign the document\n"
                  << "2. verify signature\n"
                  << "3. get verify certificate\n"
                  << "0. exit\n";
    }
}
