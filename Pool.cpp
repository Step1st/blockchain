#include "Pool.h"

void Pool::addTransaction(const Transaction& transaction)
{
	if (!(std::count(transactions.begin(), transactions.end(), transaction)))
	{
		transactions.push_back(transaction);
	}
}

void Pool::removeTransactions(std::vector<Transaction> tx_to_remove)
{
	for (auto& tx : tx_to_remove)
	{
		std::remove(transactions.begin(), transactions.end(), tx);
	}
}

std::vector<Transaction> Pool::getTransactions()
{
	if (transactions.size() <= BLOCK_TX_SIZE)
	{
		std::vector<Transaction> selected_transactions(transactions);
		return selected_transactions;
	}
	else
	{
		std::vector<Transaction> selected_transactions;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::mt19937 generator(seed);
		for (size_t i = 0; i < BLOCK_TX_SIZE; i++)
		{
			std::uniform_int_distribution<int> distribution(0, (transactions.size() - 1));
			const int index = distribution(generator);
			selected_transactions.push_back(transactions[index]);
		}

		return selected_transactions;
	}
}

bool Pool::empty()
{
	if (transactions.empty())
		return true;
	else
		return false;
}
