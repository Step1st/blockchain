#include "Blockchain.h"

Blockchain::Blockchain()
{

}

Blockchain::~Blockchain()
{

}

void Blockchain::addBlock(const Block& block)
{
	std::string filename = "blockchain/block" + std::to_string(blockchain.size()) + ".txt";
	std::ofstream output;
	output << block;
	output.close();
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
