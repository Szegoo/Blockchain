#include <iostream>
#include <vector>
#include "sha256.h"
#include <time.h>
#include <math.h>
#include <openssl/rsa.h>
#include "blockchain.h"
#include "rsa.hpp"
using std::string;
using std::cout;
using std::endl;
using std::vector;

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
            cout << "-transaction: " << endl;
            cout << "--sender: " << transaction.sender << endl;
            cout << "--reveiver: " << transaction.receiver << endl;
            cout << "--amount: " << transaction.amount << endl;
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
        vector<Block> blocks;
        unsigned int lastBlock;
        Blockchain(int test) {
            //making the genesis block
            lastBlock = 0;
            Transaction firstTransaction(ZERO_HASH, ZERO_HASH, 0,
            ZERO_HASH);
            Block genesisBlock(0, ZERO_HASH, firstTransaction);
            blocks.push_back(genesisBlock);
        }
        void addBlock(Transaction transaction) {
            lastBlock++;
            Block newBlock(lastBlock, blocks.at(lastBlock-1).hash,
            transaction);
            blocks.push_back(newBlock);
            mine(blocks.at(lastBlock).nonce);
        }
        void mine(uint nonce) {
            cout << "Mining ⛏️" << endl;
            uint solution = 1;
            while(true) {
                string hash = createHash(blocks.at(lastBlock), solution);
                if(hash.substr(0, 4) == "0000") {
                    blocks.at(lastBlock).hash = hash;
                    cout << "Solution: " << std::to_string(solution) << endl;
                    cout << "Hash: " << hash << endl;
                    break;
                }
                solution++;
            }
        }
        void displayBlocks() {
            for(int i = 0; i <= lastBlock; i++) {
                blocks.at(i).displayBlock();
            }
        }
};
class Wallet {
    public:
        string publicKey;
        string privateKey;
        Wallet() {
            createKeys();
        }
};
int main () {
    Transaction myTransaction("fd0lxjklfdso", "xx00xwlf8",
    5, "x0fjnldfxz");
    Blockchain myBlockchain(2);
    myBlockchain.addBlock(myTransaction);
    myBlockchain.addBlock(myTransaction);
    myBlockchain.addBlock(myTransaction);
    myBlockchain.displayBlocks();
    return 0;
}