#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <random>

#include "Pool.h"
#include "Transaction.h"
#include "Block.h"
#include "Blockchain.h"
#include "hash.h"
#include "User.h"

void generateUsers(std::vector<User>& users);
void generatePool(Pool& pool, std::vector<User>& users);

int main() {
	std::vector<User> users;
	Pool pool;
	Blockchain blockchain;

	std::vector<double> total_time;

	int i = 1;

	std::cout << "Generating users...\n";
	generateUsers(users);
	std::cout << "Generating pool...\n";
	generatePool(pool, users);

	const int pool_size_start = pool.size();
	int timeout_number = 0;
	uint64_t balance_before = 0;
	for (auto& user : users)
	{
		balance_before += user.getBalance();
	}

	while (!pool.empty())
	{
		Block block(blockchain.getLastHash());
		std::vector<Transaction> tx_buffer(pool.getTransactions());
		block.addTransactions(tx_buffer);
		std::cout << "Mining Block " << i << "\n";
		auto start = std::chrono::high_resolution_clock::now();
		
		if (block.mine())
		{
			std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
			std::cout << "Block finished\nTime: " << diff.count() << "s\n" << std::endl;
			total_time.push_back(diff.count());
			block.doTransactions(users);
			pool.removeTransactions(tx_buffer);
			blockchain.addBlock(block);
			i++;
		}
		else
		{
			std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
			total_time.push_back(diff.count());
			std::cout << "Block mining timeout\n\n";
			timeout_number++;
		}
			
		tx_buffer.clear();
	}
	std::ofstream output("user_end.txt");
	uint64_t balance_after = 0;
	for (auto& user : users)
	{
		balance_after += user.getBalance();
		output << user;
		output << "----------------------------------------\n";
	}
	output.close();
	std::cout << "-------------------------" << std::endl;

	std::cout << "Time elapsed: " << std::accumulate(total_time.begin(), total_time.end(), 0.0) << "s\n";
	std::cout << "Blocks mined: " << i-1 << "\n";
	std::cout << "Timeouts: " << timeout_number << "\n";
	std::cout << "Transaction difference: " << pool_size_start - blockchain.getTxNumber() << "\n";
	std::cout << "Balance difference: " << balance_after - balance_before << "\n";

	return 0;
}

void generateUsers(std::vector<User>& users) {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<uint64_t> distribution(2000, 100000);
	std::ofstream output("user_begin.txt");
	std::stringstream ofbuf;

	for (size_t i = 0; i < USER_NUMBER; i++)
	{
		User temp("user" + std::to_string(i + 1), distribution(generator));
		output << temp;
		output << "----------------------------------------\n";

		users.push_back(temp);
	}
}

void generatePool(Pool& pool, std::vector<User>& users) {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> distribution_users(0, users.size()-1);
	std::uniform_int_distribution<uint64_t> distribution_amount(1, 500);
	std::ofstream output("tx_pool.txt");

	for (size_t i = 0; i < TX_NUMBER; i++)
	{
		User user_1 = users[distribution_users(generator)];
		User user_2 = users[distribution_users(generator)];
		uint64_t amount = distribution_amount(generator);

		while (user_1 == user_2);
		{
			User user_1 = users[distribution_users(generator)];
		}

		while (user_1.getBalance() < amount)
		{
			amount = distribution_amount(generator);
		}

		Transaction tx = user_1.createTransaction(user_2.getAdress(), amount);
		output << tx;
		output << "---------------------\n";
		pool.addTransaction(tx);
	}
	output.close();
}
