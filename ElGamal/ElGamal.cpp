#include "ElGamal.h"
#include<iostream>

int main()
{
    /*
        公钥（p，g,g1）
        私钥(a)
    */
    unsigned long long p = generateLargePrime();
    std::cout << "随机素数p："<< p << std::endl;
    long long g = chooseRandomGenerator(p);
    std::cout << "生成元g：" << g << std::endl;
    unsigned long long a = chooseRandomAlpha(p);
    std::cout << "随机数a：" << a << std::endl;
    unsigned long long g1 = modPow(g, a, p);
    std::cout << "g1：" << g1 << std::endl;


    unsigned long long r = chooseRandomAlpha(p);
    std::cout << "随机数r：" << r << std::endl;

    //unsigned long long  m = 254;
    char m[] = "Hi,this is ElGamal!";
    std::cout << "明文m：" << m << std::endl;

    //unsigned long long cipher[sizeof(m) / sizeof(char) - 1][2];
    unsigned long long cipher[sizeof(m) / sizeof(char)];
    unsigned long long key = encryptC1(g, r, p);
    for (int i = 0; i < sizeof(m) / sizeof(char)-1; i++)
    {
        cipher[i] = encryptC2(g1, r, p, (unsigned long long)m[i]);
    }

    std::cout << "密文：" << std::endl;
    for (int i = 0; i < sizeof(m) / sizeof(char) - 1; i++)
    {
        std::cout << cipher[i];
        std::cout << "\t";
        if(i%2!=0) std::cout << std::endl;
    }
    std::cout << std::endl;


    for (int i = 0; i < sizeof(m) / sizeof(char) - 1; i++)
    {
        cipher[i] = decrypt(key, cipher[i], a, p);
    }
    std::cout << "解密后明文：" << std::endl;
    for (int i = 0; i < sizeof(m) / sizeof(char) - 1; i++)
    {
        std::cout << (char)cipher[i];
    }
    
    //unsigned long long C1 = encryptC1(g, r, p);
    //unsigned long long C2 = encryptC2(g1, r, p, (unsigned long long)m);
    //std::cout << "密文C1：" << C1 << std::endl;
    //std::cout << "密文C2：" << C2 << std::endl;

    //unsigned long long dm = decrypt(C1, C2, a, p);
    //std::cout << "明文dm：" << dm << std::endl;


    return 0;
}