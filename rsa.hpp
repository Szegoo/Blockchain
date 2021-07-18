#include <iostream>
#include<vector>
using std::string;
int n;

bool gcd(int a, int b)
{          
	if (a == 0) {
		if (b > 1)
			return false;
		else
			return true;
	 }
    return gcd(b % a, a); 
}

bool isPrime(int a)
{
	for (int i = a-1; i > 1; i--) {
		if (a%i == 0) {
			return false;
		}
	}
	return true;
}
int nearPrime(int a)
{
	do {
		if (isPrime(a))return a;
		a++;
	} while (true);
}


// Choose a random coprime between 1 and b
int Coprime(int a, int b)
{
	std::vector<int> coprimes;
	for (int i = 2; i < b; i++) {
		if (gcd(i, a) && gcd(i, b))
			coprimes.push_back(i);
	}
	return coprimes[rand()%coprimes.size()];
}

int xgcd(int a, int b, int & x, int & y)
{
    if(b == 0) {
       x = 1;
       y = 0;
       return a;
    }

    int x1, y1, gcd = xgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int cdn(int c, int d, int n)
{
	int value = 1;
   while( d > 0 )
   {
      value *= c;
      value %= n;
      d--;
   }
   return value;
}

int decryptionKey(int publicKey, int phi){
	int x, y;
	xgcd(publicKey, phi, x, y);
	if (x >= 0)
		return x;
	else
		return phi + x;
}
std::vector<int> createKeys(){
	int privateKey = 7;
	int p = nearPrime(privateKey);
	int q = nearPrime(p +2);
	n = p*q; //public
	int phi =(p-1)*(q-1);
	int publicKey = Coprime(n,phi);
	privateKey = decryptionKey(publicKey, phi);
	std::vector<int> keys;
	keys.push_back(publicKey);
	keys.push_back(privateKey);
	return keys;

}
std::string encrypt(std::string message, int publicKey, int n){
		for(auto &a: message){
			a = cdn(a-97, publicKey,n);
		}
		return message;
}
std::string decrypt(std::string message,int privateKey,int n ){
		for (auto &a : message )
		{
			a = 97+cdn(a, privateKey,n);
		}
		return message;
}