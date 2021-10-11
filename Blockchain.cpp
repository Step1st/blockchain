#include "Blockchain.h"

void Blockchain::addBlock(const Block& block)
{
    blockchain.push_back(block);
}

const std::string Blockchain::getLastHash()
{
	if (blockchain.empty())
	{
		return std::string('0', HASH_LENGHT);
	}
    return blockchain.back().getHash();
}
