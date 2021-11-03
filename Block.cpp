#include "Block.h"

const std::string Block::merkleRoot()
{
	std::vector<std::string> merkle;

	for (auto& tx : block_transactions) {
		merkle.push_back(hash(hash(tx.getID())));
	}

	if (merkle.empty()) {
		return "null";
	}
	if (merkle.size() == 1) {
		return merkle[0];
	}

	while (merkle.size() != 1)
	{
		std::vector<std::string> temp;

		if (merkle.size() % 2 != 0) {
			merkle.push_back(merkle.back());
		}
		for (size_t i = 0; i < merkle.size(); i+=2)
		{
			temp.push_back(hash(hash(merkle[i] + merkle[i + 1])));
		}
		merkle = temp;
	}
	return merkle[0];
}

Block::Block(std::string hash)
{
	timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	version = VERSION;
	prev_hash = hash;
}

Block::Block(std::string hash, const std::vector<Transaction>& transactions)
{
	prev_hash = hash;
	timestamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	version = VERSION;
	block_transactions = transactions;
	merkle_root = merkleRoot();
}

Block::~Block(){}

void Block::addTransactions(const std::vector<Transaction>& transactions)
{
	block_transactions = transactions;
	merkle_root = merkleRoot();
}

bool Block::mine(std::atomic_bool& flag)
{
	std::mt19937 generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<uint64_t> distribution(0, UINT64_MAX);
	int i = 0;
	while ((block_hash = hashBlock()).substr(0, difficulty) != std::string(difficulty, '0')) {
		if (!flag)
		{
			return false;
		}
		if (i > 10000 * difficulty)
		{
			return false;
		}
		nonce = distribution(generator);
		i++;
	}
	flag = false;
	mined = true;
	return true;
}

const std::string Block::getHash()
{
	return block_hash;
}

const std::vector<Transaction>& Block::getTransactions()
{
	return block_transactions;
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


void Block::doTransactions(std::map<std::string, User>& users)
{
	for (Transaction& tx : block_transactions)
	{
		users[tx.getSender()].removeBalance(tx.getAmount());
		users[tx.getReceiver()].addBalance(tx.getAmount());
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