#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <chrono>

#include "Consts.h"
#include "hash.h"
#include "Transaction.h"
#include "User.h"

class Block
{
	std::string block_hash = "";
	std::string prev_hash = "";
	uint32_t timestamp;
	std::string version;
	std::string merkle_root = "";
	uint64_t nonce = 0;
	int difficulty = 3;
	bool mined = false;

public:
	int thread = 0;

	std::vector<Transaction> block_transactions;

public:
	Block(std::string hash);
	Block(std::string hash, const std::vector<Transaction>& transactions);
	~Block();
	const std::string merkleRoot();
	const std::string getHash();
	const std::vector<Transaction>& getTransactions();
	const std::string hashBlock();
	const uint64_t getTxNumber();
	const bool get_mined() { return mined; }
	void addTransactions(const std::vector<Transaction>& transactions);
	bool mine(std::atomic_bool& flag);
	void doTransactions(std::map<std::string, User>& users);
	
	friend std::ostream& operator<<(std::ostream& os, const Block& block);
};

