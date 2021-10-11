#include "Transaction.h"


Transaction::Transaction(std::string sender_, std::string receiver_, uint64_t amount_)
{
    sender = sender_;
    receiver = receiver_;
    amount = amount_;
    std::stringstream tx_info;
    tx_info << sender << receiver << amount;
    id = hash(tx_info.str());
}

Transaction::Transaction()
{
    sender = "";
    receiver = "";
    amount = 0;
    id = "";
}

Transaction::~Transaction(){}

bool Transaction::operator==(const Transaction& tx)
{
    return id == tx.id && sender == tx.sender && receiver == tx.receiver && amount == tx.amount;
}

std::ostream& operator<<(std::ostream& os, const Transaction& tx)
{
    os << tx.id << "\n" << tx.sender << "\n" << tx.receiver << "\n" << tx.amount << "\n";
    return os;
}
