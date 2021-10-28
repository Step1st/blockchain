#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <random>

#include "Pool.h"
#include "Transaction.h"
#include "Block.h"
#include "Blockchain.h"
#include "hash.h"
#include "User.h"


void generateUsers(std::map<std::string, User>& users);
void generatePool(Pool& pool, std::map<std::string, User>& users);

int main() {
	auto begining = std::chrono::high_resolution_clock::now();
	std::map<std::string, User> users;
	Pool pool;
	Blockchain blockchain;

	std::vector<double> total_time;

	int i = 1;

	std::cout << "Generating users...\n";
	generateUsers(users);
	std::cout << "Generating pool...\n\n";
	generatePool(pool, users);

	const int pool_size_start = pool.size();
	int timeout_number = 0;
	uint64_t balance_before = 0;
	for (auto& [key, user] : users)
	{
		balance_before += user.getBalance();
	}

	uint64_t mining_var = 10000;
	while (!pool.empty())
	{
		std::vector<Block> blocks;
		for (size_t i = 0; i < 5; i++)
		{
			blocks.emplace_back(blockchain.getLastHash(), pool.getTransactions(users));
		}
		char letter = 'a';
		for (auto& block : blocks)
		{
			std::cout << "\nMining Block " << i << std::string(1,letter)+"\n";
			auto start = std::chrono::high_resolution_clock::now();
			if (block.mine(mining_var))
			{
				std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
				std::cout << "Block finished\nTime: " << std::fixed << diff.count() << "s\n" << std::endl;
				total_time.push_back(diff.count());
				block.doTransactions(users);
				pool.removeTransactions(block.getTransactions());
				blockchain.addBlock(block);
				i++;
				mining_var = 10000;
				std::cout << "-------------------------" << std::endl;
				break;
			}
			else
			{
				std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
				total_time.push_back(diff.count());
				std::cout << "Block " << i << std::string(1,letter)+" mining timeout\n\n";
				timeout_number++;
				letter++;
			}
			if (letter == 'f') {
				mining_var += 5000;
				std::cout << "-------------------------\n";
			}
		}
	}
	std::ofstream output("user_end.txt");
	uint64_t balance_after = 0;
	for (auto& [pk, user] : users)
	{
		balance_after += user.getBalance();
		output << user;
		output << "----------------------------------------\n";
	}
	output.close();

	std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - begining;
	std::cout << "\nTime elapsed: " << time.count() << "s\n";
	std::cout << "Total mining time: " << std::accumulate(total_time.begin(), total_time.end(), 0.0) << "s\n";
	std::cout << "Blocks mined: " << i-1 << "\n";
	std::cout << "Timeouts: " << timeout_number << "\n";
	std::cout << "Transactions removed: " << pool_size_start - blockchain.getTxNumber() << "\n";
	std::cout << "Balance difference: " << balance_after - balance_before << "\n";

	return 0;
}

void generateUsers(std::map<std::string, User>& users) {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<uint64_t> distribution(2000, 100000);
	std::ofstream output("user_begin.txt");

	int i = 0;
	while (users.size() != USER_NUMBER)
	{
		User temp;
		do 
		{
			temp = User("user" + std::to_string(i + 1), distribution(generator));
			i++;
		}
		while (users.find(temp.getAdress()) != users.end());
		output << temp;
		output << "----------------------------------------\n";
		users[temp.getAdress()] = temp;
	}
}

void generatePool(Pool& pool, std::map<std::string, User>& users) {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> distribution_users(0, users.size()-1);
	std::uniform_int_distribution<uint64_t> distribution_amount(1, 500);
	std::ofstream output("tx_pool.txt");

	for (size_t i = 0; i < TX_NUMBER; i++)
	{
		auto user_1 = users.begin();
		auto user_2 = users.begin();
		std::advance(user_1, distribution_users(generator));
		std::advance(user_2, distribution_users(generator));
		uint64_t amount = distribution_amount(generator);

		while (user_1 == user_2);
		{
			user_1 = users.begin();
			std::advance(user_1, distribution_users(generator));
		}

		auto& [addr1, user1] = (*user_1);
		auto& [addr2, user2] = (*user_2);

		Transaction tx = user1.createTransaction(addr2, amount);
		output << tx;
		output << "---------------------\n";
		pool.addTransaction(tx);
	}
	output.close();
}
