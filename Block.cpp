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

	while ((block_hash = hashBlock()).substr(0, difficulty) != std::string('0', difficulty));
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


//void doTransaction(std::vector<User> users);
//void Block::doTransaction(std::vector<User> users)
//{
//	for (auto& tx : block_transactions)
//	{
//		auto sender_ = std::find_if(users.begin(), users.end(), [tx](User a) {a.getAdress() == tx.sender; });
//		auto receiver_ = std::find_if(users.begin(), users.end(), [tx](User a) {a.getAdress() == tx.receiver; });
//
//		(*sender_).balance += tx.amount;
//		(*receiver_).balance -= tx.amount;
//	}
//
//}

