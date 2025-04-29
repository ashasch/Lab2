// rsa_lib.h
#pragma once

#ifdef RSALIBRARY_EXPORTS
#define RSA_API __declspec(dllexport)
#else
#define RSA_API __declspec(dllimport)
#endif

#include <utility>
#include <string>

// Структура для зберігання ключа
struct RSAKey {
    long long exponent;
    long long modulus;
};

// Функції бібліотеки
extern "C" {
    RSA_API void generateKeys(RSAKey* publicKey, RSAKey* privateKey, long long p, long long q);
    RSA_API long long encrypt(long long message, RSAKey publicKey);
    RSA_API long long decrypt(long long encrypted, RSAKey privateKey);
}