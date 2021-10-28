#pragma once
#include <vector>
#include <random>
#include <chrono>
#include <map>

#include "Transaction.h"
#include "Consts.h"
#include "User.h"


class Pool
{
	std::vector<Transaction> transactions;

public:
	void addTransaction(const Transaction& transaction);
	void removeTransactions(std::vector<Transaction> tx_to_remove);
	std::vector<Transaction> getTransactions(std::map<std::string, User>& users);
	bool empty();
	int size();
};

