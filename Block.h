#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "Consts.h"
#include "hash.h"
#include "Transaction.h"

class Block
{
public:
	std::string prev_hash = "";
	std::string hash = "";
	uint32_t timestamp;
	std::string version;
	std::string merkle_root = "";
	uint32_t nonce = 0;
	uint32_t difficulty = 1;

	std::vector<Transaction> block_transactions;

public:
	Block();
	~Block();
	std::string getHash();
	std::string Hash();
};

