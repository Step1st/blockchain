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
	void addBalance(uint64_t amount);
	void removeBalance(uint64_t amount);

	const Transaction createTransaction(std::string receiver, uint64_t amount);
	friend std::ostream& operator<<(std::ostream& os, const User& user);
	bool operator== (const User& user);
};