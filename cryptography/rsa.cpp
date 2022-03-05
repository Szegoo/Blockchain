#include<iostream>
#include<math.h>
#define MAX_NUM 10000

using std::cout;

void test(long e, double d, long n);

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
		num = rand() % MAX_NUM;
	}while(!isPrime(num) || num == p);
	return num;	
}

int main() {
   long p = getRandomPrimeNumber();
   long q = getRandomPrimeNumber(p);
   long n = p*q;
   long z = (p-1)*(q-1);
   long e = 11;

   while(e<z) {
      long track = gcd(e, z);
      if(track==1)
         break;
      else
         e++;
   }

   double d1 = (double)1/e;
   double d=fmod(d1,z);

   cout <<"p="<<p<<"\n";
   cout <<"q="<<q<<"\n";
   cout <<"z="<<z<<"\n";
   cout <<"e="<<e<<"\n";
   cout <<"d="<<d<<"\n";
   
   test(e, d, n);

   return 0;
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
