#pragma once

#include <vector>

#include "Pool.h"
#include "Block.h"
#include "hash.h"

class Blockchain
{
	std::vector<Block> blockchain;

	static Block block;

public:
	Blockchain();
	~Blockchain();

	void startBlock(std::vector<Transaction> transactions);
};

