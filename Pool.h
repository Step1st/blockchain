#pragma once
#include <vector>
#include <random>
#include <chrono>

#include "Transaction.h"
#include "Consts.h"


class Pool
{
	std::vector<Transaction> transactions;

public:
	void addTransaction(const Transaction& transaction);
	void removeTransactions(std::vector<Transaction> tx_to_remove);
	std::vector<Transaction> getTransactions();
	bool empty();
	int size();
};

