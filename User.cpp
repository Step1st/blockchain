#include "User.h"

User::User(std::string name_, uint64_t balance_) {
	name = name_;
	balance = balance_;
	public_key = hash(name);
}

User::User(const User& user)
{
	name = user.name;
	balance = user.balance;
	public_key = user.public_key;
}

User::User(User&& user) noexcept
{
	name = user.name;
	balance = user.balance;
	public_key = user.public_key;
	user.name = "";
	user.balance = 0;
	user.public_key = "";
}

const std::string User::getAdress()
{
	return public_key;
}

const uint64_t User::getBalance()
{
	return balance;
}

const Transaction User::createTransaction(std::string receiver, uint64_t amount)
{
	return Transaction(public_key, receiver, amount);
}

std::ostream& User::operator<<(std::ostream& os)
{
	os << "Name: " + name << "\n"
	   << "Public_key: " + public_key << "\n"
	   << "Balance: " + std::to_string(balance) << "\n";

	return os;
}

bool User::operator==(const User& user)
{
	return name == user.name && public_key == user.public_key && balance == user.balance;
}
