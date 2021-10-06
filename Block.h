#pragma once
#include "includes.h"

class Block
{
public:
	std::string prev_hash;
	uint32_t timestamp;
	std::string version;
	std::string merkle_root;
	uint32_t nonce = 0;
	uint32_t difficulty = 1;
};

