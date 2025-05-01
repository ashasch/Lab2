// rsa_lib.cpp
#include "pch.h"
#include "rsa_lib.h"
#include <cmath>
#include <random>
#include <algorithm>

namespace {
    // Допоміжні функції
    long long gcd(long long a, long long b) {
        while (b != 0) {
            long long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    long long modInverse(long long a, long long m) {
        a = a % m;
        for (long long x = 1; x < m; x++) {
            if ((a * x) % m == 1)
                return x;
        }
        return 1;
    }

    bool isPrime(long long n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (long long i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        }
        return true;
    }
}

// Генерація ключів
RSA_API void generateKeys(RSAKey* publicKey, RSAKey* privateKey, long long p, long long q) {
    if (!isPrime(p) || !isPrime(q) || p == q) {
        throw std::invalid_argument("p and q must be distinct prime numbers");
    }

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    // Вибираємо e (відкритий ключ)
    long long e = 17; // Поширене значення для e
    while (gcd(e, phi) != 1) {
        e++;
    }

    // Обчислюємо d (закритий ключ)
    long long d = modInverse(e, phi);

    // Заповнюємо структури ключів
    publicKey->exponent = e;
    publicKey->modulus = n;
    privateKey->exponent = d;
    privateKey->modulus = n;
}

// Шифрування
RSA_API long long encrypt(long long message, RSAKey publicKey) {
    if (message >= publicKey.modulus) {
        throw std::invalid_argument("Message must be less than modulus");
    }
    return static_cast<long long>(pow(message, publicKey.exponent)) % publicKey.modulus;
}

// Розшифрування
RSA_API long long decrypt(long long encrypted, RSAKey privateKey) {
    return static_cast<long long>(pow(encrypted, privateKey.exponent)) % privateKey.modulus;
}