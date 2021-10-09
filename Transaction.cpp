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

std::ostream& Transaction::operator<<(std::ostream& os)
{
    os << id << "\n" << sender << "\n" << receiver << "\n" << amount << "\n";
    return os;
}

bool Transaction::operator==(const Transaction& tx)
{
    return id == tx.id && sender == tx.sender && receiver == tx.receiver && amount == tx.amount;
}
