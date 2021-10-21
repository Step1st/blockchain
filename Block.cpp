#include "Block.h"

void Block::merkleRoot()
{
	std::stringstream transactions;
	for (auto& tx : block_transactions)
	{
		transactions << tx.getID();
	}
	merkle_root = hash(transactions.str());
}

Block::Block(std::string hash)
{
	timestamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	version = VERSION;
	prev_hash = hash;
}

Block::~Block(){}

void Block::addTransactions(const std::vector<Transaction>& transactions)
{
	block_transactions = transactions;
	merkleRoot();
}

bool Block::mine()
{
	int i = 0;
	while ((block_hash = hashBlock()).substr(0, difficulty) != std::string(difficulty, '0')) {
		std::mt19937 generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<uint64_t> distribution(0, UINT64_MAX);
		nonce = distribution(generator);
		i++;
		if (0 && i > 50000*difficulty)
		{
			return false;
		}
	}
	return true;
}

const std::string Block::getHash()
{
	return block_hash;
}

const std::string Block::hashBlock()
{
	std::stringstream block;
	block << prev_hash << timestamp << version << merkle_root << nonce << difficulty;
	return hash(hash(block.str()));
}

const uint64_t Block::getTxNumber()
{
	return block_transactions.size();
}


void Block::doTransactions(std::vector<User>& users)
{
	for (Transaction& tx : block_transactions)
	{
		auto sender_ = std::find_if(users.begin(), users.end(), [&tx](User a) { return a.getAdress() == tx.getSender(); });
		auto receiver_ = std::find_if(users.begin(), users.end(), [&tx](User a) { return a.getAdress() == tx.getReceiver(); });

		(*sender_).removeBalance(tx.getAmount());
		(*receiver_).addBalance(tx.getAmount());
	}

}

std::ostream& operator<<(std::ostream& os, const Block& block)
{
	os << "hash: " << block.block_hash << "\n"
		<< "prev_hash: " << block.prev_hash << "\n"
		<< "timestamp: "  << block.timestamp << "\n"
		<< "version: " << block.version << "\n"
		<< "merkle_root: " << block.merkle_root << "\n"
		<< "nonce: " << block.nonce << "\n"
		<< "difficulty: " << block.difficulty << "\n"
		<< "Number of transaction: " << block.block_transactions.size() << "\n";
	for (auto& tx : block.block_transactions)
	{
		os << "------------------\n" << tx;
	}
	return os;
}