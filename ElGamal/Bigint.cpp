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
    std::uniform_int_distribution<unsigned long long> dist(100000000, 999999999);

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


//生成元g
bool is_generator(long long g, long long p)
{
    // 找到 p-1 的所有质因数
    std::vector<long long> factors;
    long long n = p - 1;
    for (long long i = 2; i <= sqrt(n); ++i) 
    {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) {
        factors.push_back(n);  // n 是质数
    }

    // 检查 g^((p-1)/q) % p 对于所有质因数 q 是否等于 1
    for (long long q : factors) 
    {
        if (modPow(g, (p - 1) / q, p) == 1) 
        {
            return false;
        }
    }
    return true;
}

long long chooseRandomGenerator(long long p)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<long long> dist(2, p - 1);

    long long g;
    // 随机选择直到找到一个生成元
    do {
        g = dist(gen);
    } while (!is_generator(g, p));  // 检查是否为生成元

    return g;
}


//随机数α
unsigned long long chooseRandomAlpha(unsigned long long p) 
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long> dist(1, p - 2);  // α 的范围是 1 到 p-2

    return dist(gen);
}

//逆元计算
unsigned long long modInverse(unsigned long long a, unsigned long long p) 
{
    return modPow(a, p - 2, p);
}

unsigned long long encryptC1(unsigned long long g, unsigned long long r, unsigned long long p)
{
    return modPow(g, r, p);
}

unsigned long long encryptC2(unsigned long long g1, unsigned long long r, unsigned long long p, unsigned long long m)
{
    return (modPow(g1, r, p) * m) % p;
}

// 解密函数
unsigned long long decrypt(unsigned long long c1, unsigned long long c2, unsigned long long a, unsigned long long p) 
{
    // 计算 c1^α % p
    unsigned long long c1_a = modPow(c1, a, p);

    // 计算 c1^α 的逆元
    unsigned long long c1_a_i = modInverse(c1_a, p);

    // 恢复明文 m
    unsigned long long m = (c2 * c1_a_i) % p;
    return m;
}