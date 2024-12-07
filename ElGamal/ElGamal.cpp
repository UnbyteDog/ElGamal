#include "ElGamal.h"
#include<iostream>

int main()
{
    /*
        ��Կ��p��g,g1��
        ˽Կ(a)
    */
    unsigned long long p = generateLargePrime();
    std::cout << "�������p��"<< p << std::endl;
    long long g = chooseRandomGenerator(p);
    std::cout << "����Ԫg��" << g << std::endl;
    unsigned long long a = chooseRandomAlpha(p);
    std::cout << "�����a��" << a << std::endl;
    unsigned long long g1 = modPow(g, a, p);
    std::cout << "g1��" << g1 << std::endl;


    unsigned long long r = chooseRandomAlpha(p);
    std::cout << "�����r��" << r << std::endl;

    unsigned long long  m = 254;
    std::cout << "����m��" << m << std::endl;
    /*char m[] = "Hi,this is ElGamal!";
    for (int i = 0; m[i] != '\0'; i++)
    {
        std::cout << m[i];
    }
    std::cout << std::endl;
    for (int i = 0; m[i] != '\0'; i++)
    {
        std::cout << (int)m[i] << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;*/

    unsigned long long C1 = encryptC1(g, r, p);

    unsigned long long C2 = encryptC2(g1, r, p, (unsigned long long)m);
    std::cout << "����C1��" << C1 << std::endl;
    std::cout << "����C2��" << C2 << std::endl;

    unsigned long long dm = decrypt(C1, C2, a, p);
    std::cout << "����dm��" << dm << std::endl;


    return 0;
}