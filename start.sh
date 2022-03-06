g++ -c blockchain.cpp -c saveToDisk.cpp ./cryptography/sha256.cpp ./cryptography/rsa.cpp
g++ -o blockchain blockchain.o saveToDisk.o sha256.o rsa.o
./blockchain