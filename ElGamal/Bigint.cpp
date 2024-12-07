#include "ElGamal.h"
#include<random>
#include <cmath>

//bool isPrime(unsigned long long n) {
//    if (n <= 1) return false;
//    if (n <= 3) return true;
//    if (n % 2 == 0 || n % 3 == 0 || n % 7 == 0) return false;
//    for (unsigned long long i = 5; i * i <= n; i += 6) {
//        if (n % i == 0 || n % (i + 2) == 0) return false;
//    }
//    return true;
//}

unsigned long long generateLargePrime() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long> dist(10000000, 99999999);

    unsigned long long num;
    do {
        num = dist(gen);  // 随机生成一个大数
    } while (!millerRabin(num));  // 判断是否为素数
    return num;
}

unsigned long long modPow(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

bool millerRabin(unsigned long long n, int k) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;

    // 计算 n - 1 = 2^s * d
    unsigned long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    // k 是测试的次数，越大越准确
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long> dist(2, n - 2);

    for (int i = 0; i < k; i++) {
        unsigned long long a = dist(gen);
        unsigned long long x = modPow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool isComposite = true;
        for (int r = 0; r < s - 1; r++) {
            x = modPow(x, 2, n);
            if (x == n - 1) {
                isComposite = false;
                break;
            }
        }

        if (isComposite) return false;
    }

    return true;  // 通过所有测试，认为是素数
}
