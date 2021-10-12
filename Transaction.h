#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "hash.h"


class Transaction
{
	std::string id;
	std::string sender;
	std::string receiver;
	uint64_t amount;

public:
	
	Transaction(std::string sender_, std::string receiver_, uint64_t amount_);
	Transaction();
	~Transaction();
	const uint64_t getAmount();
	const std::string getID();
	const std::string getSender();
	const std::string getReceiver();

	friend std::ostream& operator<<(std::ostream& os, const Transaction& tx);
	bool operator==(const Transaction& transaction);
};

std::ostream& operator<<(std::ostream& os, const Transaction& tx);

