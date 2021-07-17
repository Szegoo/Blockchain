#include <iostream>
#include "sha256.h"
#include <time.h>
#include <math.h>
using std::string;
using std::cout;
using std::endl;

string ZERO_HASH = "0000000000000000000000000000000000000000000000000000000000000000";

class Transaction {
    public:
        string sender;
        string receiver;
        int amount;
        string signature;
        Transaction(string _sender, string _receiver,
        int _amount, string _signature) {
            sender = _sender;
            receiver = _receiver;
            amount = _amount;
            signature = _signature;
        }
        Transaction(){}
};
class Block {
    public:
        long nonce;
        int index;
        int timestamp;
        string prevHash;
        string hash = "";
        Transaction transaction;
        Block(int _index, string _prevHash,
        Transaction _transaction) {
            srand(time(0));
            time_t seconds;
            seconds = time(NULL);
            index = _index;
            timestamp = seconds;
            prevHash = _prevHash;
            nonce = rand();
            transaction = _transaction;
        }
        void displayBlock() {
            cout << "Block #" << index << endl;
            cout << "-hash: " << hash << endl;
            cout << "-prevHash: " << prevHash << endl;
            cout << "-nonce: " << nonce << endl;
            cout << "-timestamp: " << timestamp << endl;
        }
        Block(){}
};
string createHash(Block block, int solution = 1) {
    return sha256(std::to_string(block.index) + 
            block.prevHash + std::to_string(block.timestamp) +
            block.transaction.signature + 
            block.transaction.receiver +
            block.transaction.sender + 
            std::to_string(block.transaction.amount)
            + std::to_string(solution));
}
class Blockchain {
    public:
        Block blocks[1000];
        unsigned int lastBlock;
        Blockchain(int test) {
            //making the genesis block
            lastBlock = 0;
            blocks[lastBlock].hash = ZERO_HASH;
            blocks[lastBlock].prevHash = ZERO_HASH;
            blocks[lastBlock].timestamp = 0;
            blocks[lastBlock].index = 0;
        }
        void addBlock(Transaction transaction) {
            lastBlock++;
            Block newBlock(lastBlock, blocks[lastBlock-1].hash,
            transaction);
            blocks[lastBlock] = newBlock;
            mine(blocks[lastBlock].nonce);
        }
        void mine(uint nonce) {
            cout << "Mining ⛏️" << endl;
            uint solution = 1;
            while(true) {
                string hash = createHash(blocks[lastBlock], solution);
                if(hash.substr(0, 4) == "0000") {
                    blocks[lastBlock].hash = hash;
                    cout << "Solution: " << std::to_string(solution) << endl;
                    cout << "Hash: " << hash << endl;
                    cout << "Substring: " << hash.substr(0, 4) << endl;
                    break;
                }
                solution++;
            }
        }
};
int main () {
    Transaction myTransaction("fd0lxjklfdso", "xx00xwlf8",
    5, "x0fjnldfxz");
    Blockchain myBlockchain(2);
    myBlockchain.addBlock(myTransaction);
    myBlockchain.blocks[1].displayBlock();
    return 0;
}