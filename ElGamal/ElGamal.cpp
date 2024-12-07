#include "ElGamal.h"
#include<iostream>
#include<string>

#define SIZE 100

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

    std::string m;
    //m = "Hi,this is ElGamal!";
    std::cout << "��������m��"<< std::endl;
    std::getline(std::cin, m);
    std::cout << "����m��"<< std::endl;
    std::cout << m << std::endl;

    unsigned long long cipher[SIZE] = { 0 };

    unsigned long long key = encryptC1(g, r, p);

    for (int i = 0; i < m.size(); i++)
    {
        cipher[i] = encryptC2(g1, r, p, (unsigned long long)m[i]);
    }

    std::cout << "���ģ�" << std::endl;
    for (int i = 0; i < m.size(); i++)
    {
        std::cout << cipher[i];
        std::cout << "\t";
        if(i%2!=0) std::cout << std::endl;
    }
    std::cout << std::endl;


    for (int i = 0; i < m.size(); i++)
    {
        cipher[i] = decrypt(key, cipher[i], a, p);
    }
    std::cout << "���ܺ����ģ�" << std::endl;
    for (int i = 0; i < m.size(); i++)
    {
        std::cout << (char)cipher[i];
    }

    
    //unsigned long long C1 = encryptC1(g, r, p);
    //unsigned long long C2 = encryptC2(g1, r, p, (unsigned long long)m);
    //std::cout << "����C1��" << C1 << std::endl;
    //std::cout << "����C2��" << C2 << std::endl;
    //unsigned long long dm = decrypt(C1, C2, a, p);
    //std::cout << "����dm��" << dm << std::endl;


    return 0;
}