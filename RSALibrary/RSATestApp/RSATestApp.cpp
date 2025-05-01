#include <iostream>
#include <cmath>
#include "../RSALibrary/rsa_lib.h"  // Шлях до вашого заголовочного файлу DLL
#pragma comment(lib, "../x64/Debug/RSALibrary.lib")

int main() {
    RSAKey publicKey, privateKey;
    generateKeys(&publicKey, &privateKey, 3, 7);
    
    long long encrypted = encrypt(12, publicKey);
    std::cout << "Encrypted: " << encrypted << std::endl;

    long long decrypted = decrypt(encrypted, privateKey);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}