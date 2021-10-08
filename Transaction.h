#pragma once
#include <iostream>
#include <string>


class Transaction
{
	std::string id;
	std::string sender;
	std::string receiver;
	uint64_t amount;

private:
	void doTransaction();
public:
	Transaction(std::string sender_, std::string receiver_, uint64_t amount_);
	Transaction();
	~Transaction();

	std::ostream& operator<<(std::ostream& os);
};

