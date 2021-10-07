#include "Transaction.h"

std::ostream& Transaction::operator<<(std::ostream& os)
{
    os << sender << "\n" << receiver << "\n" << amount << "\n";
    return os;
}
