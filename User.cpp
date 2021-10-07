#include "User.h"

User::User(std::string name_, uint64_t balance_) {
	name = name_;
	balance = balance_;
	public_key = hash(name);
}

std::ostream& User::operator<<(std::ostream& os)
{
	os << "Name: " + name << "\n"
	   << "Public_key: " + public_key << "\n"
	   << "Balance: " + std::to_string(balance) << "\n";

	return os;
}