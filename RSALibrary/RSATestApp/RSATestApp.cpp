#include <iostream>
#include <cmath>
#include "Windows.h"
//#include "../RSALibrary/rsa_lib.h"  // Шлях до вашого заголовочного файлу DLL
//#pragma comment(lib, "../x64/Debug/RSALibrary.lib")

struct RSAKey {
    long long exponent;
    long long modulus;
};

typedef void (*generateKeys)(RSAKey*, RSAKey*, long long, long long);
typedef long long (*encrypt)(long long, RSAKey);
typedef long long (*decrypt)(long long, RSAKey);

int main() {
    HINSTANCE hLib = LoadLibrary(L"RSALibrary.dll");
    if (!hLib) {
        std::cerr << "Cannot load DLL\n";
        return 1;
    }

    auto generateKeysImpl = (generateKeys)GetProcAddress(hLib, "generateKeys");
    auto encryptImpl = (encrypt)GetProcAddress(hLib, "encrypt");
    auto decryptImpl = (decrypt)GetProcAddress(hLib, "decrypt");

    RSAKey publicKey, privateKey;
    generateKeysImpl(&publicKey, &privateKey, 3, 7);
    
    long long encrypted = encryptImpl(12, publicKey);
    std::cout << "Encrypted: " << encrypted << std::endl;

    long long decrypted = decryptImpl(encrypted, privateKey);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}