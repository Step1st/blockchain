#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <random>
#include <thread>
#include <atomic>

#include "Pool.h"
#include "Transaction.h"
#include "Block.h"
#include "Blockchain.h"
#include "hash.h"
#include "User.h"

std::atomic_bool f_mine;

void generateUsers(std::map<std::string, User>& users);
void generatePool(Pool& pool, std::map<std::string, User>& users);
void mining_instance(Block& block, uint64_t mining_attemps);

int main() {
	auto begining = std::chrono::high_resolution_clock::now();
	std::map<std::string, User> users;
	Pool pool;
	Blockchain blockchain;

	std::vector<double> total_time;

	std::cout << "Generating users...\n";
	generateUsers(users);
	std::cout << "Generating pool...\n";
	generatePool(pool, users);

	const int pool_size_start = pool.size();
	int timeout_counter = 0;
	uint64_t balance_before = 0;
	for (auto& [key, user] : users)
	{
		balance_before += user.getBalance();
	}

	int i = 1;
	uint64_t mining_attemps = 10000;
	while (!pool.empty())
	{
		int i_copy = i;
		std::vector<Block> blocks;
		for (size_t i = 0; i < THREAD_COUNT; i++)
		{
			blocks.emplace_back(blockchain.getLastHash(), pool.getTransactions(users));
			blocks[i].thread = i+1;
		}
		std::vector<std::thread> threads;
		threads.reserve(THREAD_COUNT);
		std::cout << "\nMining Block " << i << "\n";
		f_mine.store(true);

		auto start = std::chrono::high_resolution_clock::now();
		for (auto& block : blocks)
		{
			threads.emplace_back(mining_instance, std::ref(block), mining_attemps);
		}
		for (auto& thread : threads)
		{
			thread.join();
		}
		std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
		total_time.push_back(diff.count());

		for (auto& block : blocks)
		{
			if (block.get_mined()) {
				std::cout << "Block " << i << " finished by thread " << block.thread << "\n\n--------------------------\n";
				block.doTransactions(users);
				pool.removeTransactions(block.getTransactions());
				blockchain.addBlock(block);
				i++;
				mining_attemps = 10000;
				break;
			}
		}
		if (i == i_copy)
		{
			std::cout << "Mining Block " << i << " failed\n\n--------------------------\n";
			timeout_counter++;
			mining_attemps += 10000;
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
	std::cout << "Total time mining: " << std::fixed << std::accumulate(total_time.begin(), total_time.end(), 0.0) << "s\n";
	std::cout << "Blocks mined: " << i-1 << "\n";
	std::cout << "Timeouts: " << timeout_counter << "\n";
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

void mining_instance(Block& block, uint64_t mining_attemps)
{
	block.mine(f_mine, mining_attemps);
}
