#pragma once
#include <vector>
#include "Transaction.h"

class Pool
{
	std::vector<Transaction> Transactions;

public:
	void addTransaction(Transaction& transaction);
	std::vector<Transaction> getTransactions();

};

