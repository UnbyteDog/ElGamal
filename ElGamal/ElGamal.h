#ifndef __ELGAMAL_H__
#define __ELGAMAL_H__

//bool isPrime(unsigned long long n);

unsigned long long modPow(unsigned long long base, unsigned long long exp, unsigned long long mod);		//øÏÀŸ√›‘ÀÀ„
bool millerRabin(unsigned long long n, int k = 5);
unsigned long long generateLargePrime();

bool is_generator(long long g, long long p);
long long chooseRandomGenerator(long long p);


unsigned long long chooseRandomAlpha(unsigned long long p);

unsigned long long encryptC1(unsigned long long g, unsigned long long r, unsigned long long p);
unsigned long long encryptC2(unsigned long long g1, unsigned long long r, unsigned long long p, unsigned long long m);


unsigned long long modInverse(unsigned long long a, unsigned long long p);
unsigned long long decrypt(unsigned long long c1, unsigned long long c2, unsigned long long alpha, unsigned long long p);


#endif