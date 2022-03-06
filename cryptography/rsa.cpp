#include<iostream>
#include<math.h>
#include "rsa.h"

using std::cout;

int UNDEFINED_P = -1;

void test(long e, double d, long n);

struct KeyPair generateKeyPair() {
   long p = getRandomPrimeNumber(UNDEFINED_P);
   long q = getRandomPrimeNumber(p);
   long n = p*q;
   long z = (p-1)*(q-1);
   long e = 11;

   calcE(&e, z);

   double d1 = (double)1/e;
   double d=fmod(d1,z);
   
   KeyPair kp;
   kp.publicKey = e;
   kp.privateKey = d;

   return kp;
}

bool isPrime(int num) {
	for(int i = 2; i < sqrt(num); i++) {
		if(num % i == 0) {
			return false;
		}
	}
	return true;
}

long getRandomPrimeNumber(long p = -1) {
	srand (time(NULL));
	long num;
	do {	
		num = rand() % MAX_PRIME_NUM;
	}while(!isPrime(num) || num == p);
	return num;	
}

int gcd(int a, int b) {
   int t;
   while(1) {
      t= a%b;
      if(t==0)
      return b;
      a = b;
      b= t;
   }
}

void calcE(long *e, long z) { 
   while(*e<z) {
      long track = gcd(*e, z);
      if(track==1)
         break;
      else
         e++;
   }
}

void test(long e, double d, long n) {
   double message = 4;
   double c = pow(message,e);
   double m = pow(c,d);
   c=fmod(c,n);
   m=fmod(m,n);
   cout<<"Original Message = "<<message;
   cout<<"\n"<<"Encrypted message = "<<c;
   cout<<"\n"<<"Decrypted message = "<<m<<"\n";
}
