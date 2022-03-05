#define MAX_PRIME_NUM 10000

struct KeyPair {
    long publicKey;
    long privateKey;
};

void calcE(long *e, long z);
int gcd(int a, int b);
bool isPrime(int num);
long getRandomPrimeNumber(long p);
struct KeyPair generateKeyPair();