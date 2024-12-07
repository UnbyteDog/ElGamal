#include "ElGamal.h"
#include<iostream>

int main()
{
    unsigned long long num = generateLargePrime();
    if (millerRabin(num)) {
        std::cout << num << " is prime!" << std::endl;
    }
    else {
        std::cout << num << " is not prime." << std::endl;
    }
    return 0;
}