#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <openssl/rsa.h>
#include "blockchain.h"
#include <openssl/pem.h>
#include "./cryptography/sha256.h"
#include "./cryptography/rsa.h"
#include "saveToDisk.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::to_string;

class Block {
    public:
        long nonce;
        int index;
        int timestamp;
        string prevHash;
        string hash = "";
        Transaction transaction;
        Block(int _index, string _prevHash,
        Transaction _transaction, int _nonce) {
            time_t seconds;
            seconds = time(NULL);
            index = _index;
            timestamp = seconds;
            prevHash = _prevHash;
            transaction = _transaction;
            nonce = _nonce;
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
        string ToCSV() {
            string res = to_string(index) + "," +to_string(nonce)
            +","+ to_string(timestamp)+","+hash+","+prevHash+
            ","+transaction.sender+","+transaction.receiver+","
            +transaction.signature +","+to_string(transaction.amount); 
            return res;
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
class Wallet {
    //working on implementing key generation
    public: 
        int nonce = 1;
        string pubKey = ZERO_HASH;
        string privKey = ZERO_HASH;
};
class Blockchain {
    public:
        vector<Block> blocks;
        unsigned int lastBlock;
        Blockchain() {
            //making the genesis block
            lastBlock = 0;
            Transaction firstTransaction(ZERO_HASH, ZERO_HASH, 0,
            ZERO_HASH);
            Block genesisBlock(0, ZERO_HASH, firstTransaction, 0);
            blocks.push_back(genesisBlock);
        }
        void addBlock(Transaction transaction, Wallet *wallet) {
            lastBlock++;
            Block newBlock(lastBlock, blocks.at(lastBlock-1).hash,
            transaction, wallet->nonce);
            blocks.push_back(newBlock);
            wallet->nonce++;
            mine(wallet->nonce);
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
        string ToCSV() {
            string csv = "index,nonce,timestamp,hash,prevhash,sender,receiver,signature,amount\n";
            for(int i = 0; i <= lastBlock; i++) {
                csv += blocks.at(i).ToCSV() + '\n';
            }
            return csv;
        }
};
int main () {
    Wallet myWallet;
    Transaction myTransaction(myWallet.pubKey, "xx00xwlf8",
    5, "x0fjnldfxz");
    Blockchain myBlockchain;
    myBlockchain.addBlock(myTransaction, &myWallet);
    myBlockchain.addBlock(myTransaction, &myWallet);
    myBlockchain.displayBlocks();
    string data = myBlockchain.ToCSV();
    saveToDisk(data);
    return 0;
}
