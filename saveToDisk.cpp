#include <iostream>
#include <fstream>
#include "saveToDisk.h"
using namespace std;

void saveToDisk(string data) {
    ofstream BlockchainFile("blockchain.csv");

    BlockchainFile << data;

    BlockchainFile.close();
}