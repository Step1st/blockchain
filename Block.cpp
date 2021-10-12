#include "Block.h"

void Block::merkleRoot()
{
	std::stringstream transactions;
	for (auto& tx : block_transactions)
	{
		transactions << tx;
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
}

void Block::mine()
{
	while ((block_hash = hashBlock()).substr(1, difficulty) != std::string(difficulty, '0')) {
		std::cout << block_hash << "\n";
		nonce++;
	}
}

const std::string Block::getHash()
{
	return block_hash;
}

const std::string Block::hashBlock()
{
	std::stringstream block;
	block << prev_hash << timestamp << version << merkle_root << nonce << difficulty;
	return hash(block.str());
}


void Block::doTransactions(std::vector<User> users)
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
	os << block.block_hash << "\n"
		<< block.prev_hash << "\n"
		<< block.timestamp << "\n"
		<< block.version << "\n"
		<< block.merkle_root << "\n"
		<< block.nonce << "\n"
		<< block.difficulty << "\n";
	return os;
}