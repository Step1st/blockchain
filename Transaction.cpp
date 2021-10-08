#include "Transaction.h"


Transaction::Transaction(std::string sender_, std::string receiver_, uint64_t amount_) {

    sender = sender_;
    receiver = receiver_;
    amount = amount_;

}

std::ostream& Transaction::operator<<(std::ostream& os)
{
    os << id << "\n" << sender << "\n" << receiver << "\n" << amount << "\n";
    return os;
}
