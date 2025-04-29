// main.cpp
#include "pch.h"
#include <iostream>
#include "rsa_lib.h"

int main() {
    try {
        // Генерація першої пари ключів
        RSAKey publicKey1, privateKey1;
        generateKeys(&publicKey1, &privateKey1, 61, 53); // p=61, q=53

        // Генерація другої пари ключів
        RSAKey publicKey2, privateKey2;
        generateKeys(&publicKey2, &privateKey2, 17, 19); // p=17, q=19

        // Тестові дані
        long long testData[] = { 88, 123, 42, 15, 99 };

        for (auto data : testData) {
            std::cout << "\n=== Testing with data: " << data << " ===\n";

            // 1. Шифрування за допомогою publicKey2
            long long e1t = encrypt(data, publicKey2);
            std::cout << "Encrypted with key2: " << e1t << std::endl;

            // 2. Розшифрування за допомогою privateKey2
            long long d1e1t = decrypt(e1t, privateKey2);
            std::cout << "Decrypted with key2: " << d1e1t << std::endl;

            // Перевірка коректності
            if (d1e1t != data) {
                std::cerr << "Error: Decrypted message doesn't match original!" << std::endl;
                return 1;
            }

            // 3. Шифрування за допомогою publicKey1
            long long e0d1e1t = encrypt(d1e1t, publicKey1);
            std::cout << "Encrypted with key1: " << e0d1e1t << std::endl;

            // 4. Розшифрування за допомогою privateKey1
            long long d0e0d1e1t = decrypt(e0d1e1t, privateKey1);
            std::cout << "Decrypted with key1: " << d0e0d1e1t << std::endl;

            // Перевірка коректності
            if (d0e0d1e1t != data) {
                std::cerr << "Error: Final decrypted message doesn't match original!" << std::endl;
                return 1;
            }

            std::cout << "Test passed successfully!\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}