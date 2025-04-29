#include <iostream>
#include "D:/RSALibrary/RSALibrary/rsa_lib.h"  // Шлях до вашого заголовочного файлу DLL
#pragma comment(lib, "D:\RSALibrary\x64\Debug\RSALibrary.lib")

int main() {
    RSAKey publicKey, privateKey;
    generateKeys(&publicKey, &privateKey, 61, 53);

    long long encrypted = encrypt(123, publicKey);
    std::cout << "Encrypted: " << encrypted << std::endl;

    long long decrypted = decrypt(encrypted, privateKey);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}

//