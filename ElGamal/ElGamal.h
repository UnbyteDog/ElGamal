#ifndef __ELGAMAL_H__
#define __ELGAMAL_H__

unsigned long long modPow(unsigned long long base, unsigned long long exp, unsigned long long mod);
bool millerRabin(unsigned long long n, int k = 5);
//bool isPrime(unsigned long long n);
unsigned long long generateLargePrime();


#endif