#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "Consts.h"
#include "hash.h"
#include "Transaction.h"
#include "User.h"

class Block
{
public:
	std::string block_hash = "";
	std::string prev_hash = "";
	uint32_t timestamp;
	std::string version;
	std::string merkle_root = "";
	uint32_t nonce = 0;
	uint32_t difficulty = 1;

	std::vector<Transaction> block_transactions;

private:
	void merkleRoot();

public:
	Block(std::string hash);
	~Block();
	const std::string getHash();
	const std::string hashBlock();
	void addTransactions(const std::vector<Transaction>& transactions);
	void mine();
	
};

