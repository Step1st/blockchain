#pragma once
#include <iostream>
#include <string>
#include <vector>
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
	uint32_t nonce = 0;
	uint32_t difficulty = 2;

	std::vector<Transaction> block_transactions;

public:
	Block(std::string hash);
	~Block();
	const std::string merkleRoot();
	const std::string getHash();
	const std::string hashBlock();
	const uint64_t getTxNumber();
	void addTransactions(const std::vector<Transaction>& transactions);
	bool mine();
	void doTransactions(std::vector<User>& users);
	
	friend std::ostream& operator<<(std::ostream& os, const Block& block);
};

