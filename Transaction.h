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
	Transaction();
	~Transaction();
	std::ostream& operator<<(std::ostream& os);
};

