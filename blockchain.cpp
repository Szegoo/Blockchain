#include <iostream>
#include "sha256.h"
#include <time.h>
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
        int nonce;
        int index;
        int timestamp;
        string prevHash;
        string hash = "";
        Transaction transaction;
        Block(int _index, string _prevHash,
        Transaction _transaction) {
            time_t seconds;
            seconds = time(NULL);
            index = index;
            timestamp = seconds;
            prevHash = _prevHash;
            transaction = _transaction;
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
        void addBlock(Block block) {
            lastBlock++;
            blocks[lastBlock] = block;
            mine(blocks[lastBlock].nonce);
        }
        void mine(uint nonce) {
            cout << "Mining ⛏️" << endl;
            uint solution = 1;
            while(true) {
                string hash = createHash(blocks[lastBlock], solution);
                if(hash.substr(0, 4) == "0000") {
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
    Block myBlock(1, "s0xy2hujsd", myTransaction);
    Blockchain myBlockchain(2);
    myBlockchain.addBlock(myBlock);
    return 0;
}