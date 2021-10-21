#include "Blockchain.h"

Blockchain::Blockchain()
{

}

Blockchain::~Blockchain()
{

}

void Blockchain::addBlock(const Block& block)
{
	std::filesystem::create_directory("blocks");
	std::string filename = "blocks/block" + std::to_string(blockchain.size()) + ".txt";
	std::ofstream output(filename);
	output << block;
	output.close();
    blockchain.push_back(block);
	
}

const uint64_t Blockchain::getTxNumber()
{
	uint64_t temp = 0;
	for (auto& block : blockchain)
	{
		temp += block.getTxNumber();
	}
	return temp;
}

const std::string Blockchain::getLastHash()
{
	if (blockchain.empty())
	{
		return std::string(HASH_LENGHT, '0');
	}
    return blockchain.back().getHash();
}
