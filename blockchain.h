#include <iostream>
using std::string;

string const ZERO_HASH = "0000000000000000000000000000000000000000000000000000000000000000";

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
