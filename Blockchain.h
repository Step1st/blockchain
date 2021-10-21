#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

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
	const uint64_t getTxNumber();
	const std::string getLastHash();
};

