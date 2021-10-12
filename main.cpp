#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
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
	int i = 1;
	generateUsers(users);
	std::cout << "Generating pool..." << std::endl;
	generatePool(pool, users);

	
	while (!pool.empty())
	{
		Block block(blockchain.getLastHash());
		std::vector<Transaction> tx_buffer;
		tx_buffer = pool.getTransactions();
		block.addTransactions(tx_buffer);
		std::cout << "Mining: " << i << std::endl;
		block.mine();
		std::cout << "Mining: " << i << " finished" << std::endl;
		block.doTransactions(users);
		pool.removeTransactions(tx_buffer);
		blockchain.addBlock(block); 
		i++;
	}
	std::cout << "finished" << std::endl;

	return 0;
}

void generateUsers(std::vector<User>& users) {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<uint64_t> distribution(1000, 100000);
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
	std::uniform_int_distribution<uint64_t> distribution_amount(1, 5000);

	for (size_t i = 0; i < TX_NUMBER; i++)
	{
		std::cout << i << std::endl;
		User user_1 = users[distribution_users(generator)];
		User user_2 = users[distribution_users(generator)];
		uint64_t amount = distribution_amount(generator);

		while (user_1 == user_2 || user_1.getBalance() < amount);
		{
			User user_1 = users[distribution_users(generator)];
		}
		while (user_1.getBalance() < amount)
		{
			amount = distribution_amount(generator);
		}

		pool.addTransaction(user_1.createTransaction(user_2.getAdress(), amount));
	}
}