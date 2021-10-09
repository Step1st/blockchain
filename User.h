#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "hash.h"
#include "Transaction.h"

class User
{
	std::string public_key;
	std::string name;
	uint64_t balance;

public:
	User(std::string, uint64_t);
	User(const User& user);
	User(User&& user) noexcept;
	~User(){};

	const std::string getAdress();
	const uint64_t getBalance();

	const Transaction createTransaction(std::string receiver, uint64_t amount);

	std::ostream& operator<<(std::ostream& os);
	bool operator== (const User& user);
};