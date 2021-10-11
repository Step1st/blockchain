#pragma once

#include <vector>
#include <string>

#include "Pool.h"
#include "Block.h"
#include "hash.h"

class Blockchain
{
	std::vector<Block> blockchain;

public:
	Blockchain();
	~Blockchain();
	void addBlock(const Block& block);
	const std::string getLastHash();
};

