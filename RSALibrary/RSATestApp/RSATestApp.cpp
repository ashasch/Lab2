#include <iostream>
#include <cmath>
#include "atlstr.h"
#include "Windows.h"
#include "../ResLibUkr/resource.h"
#include "../ResLibEng/resource.h"
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
    SetConsoleOutputCP(CP_WINUNICODE);
    SetConsoleCP(CP_WINUNICODE);


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
    std::wcout << "Encrypted: " << encrypted << std::endl;

    long long decrypted = decryptImpl(encrypted, privateKey);
    std::wcout << "Decrypted: " << decrypted << std::endl;

    std::wcout << u8"Select Language: English - 1, Солов'їна - 0" << std::endl;
    char langChoice;
    std::cin >> langChoice;
    HINSTANCE hLangLib{};

    if (langChoice == '1') {
        hLangLib = LoadLibrary(L"ResLibEng.dll");
        if (!hLangLib) {
            std::cerr << "Cannot load DLL\n";
            return 1;
        }
    }
    if (langChoice == '0') {
        hLangLib = LoadLibrary(L"ResLibUkr.dll");
        if (!hLangLib) {
            std::cerr << "Cannot load DLL\n";
            return 1;
        }
        std::locale::global(std::locale("uk_UA.utf8"));
    }

    for (size_t i = 0; i < 6; i++)
    {
        // сорі за костильну реалізацію, але пох
        auto curId = IDS_STRING101 + i;
        wchar_t buffer[256];

        int len = LoadStringW(hLangLib, curId, buffer, sizeof(buffer) / sizeof(wchar_t));
        if (len == 0) {
            std::wcerr << L"Не вдалося завантажити рядок\n";
            return 1;
        }

        std::wcout << buffer << std::endl;
    }

    return 0;
}
