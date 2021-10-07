#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "hash.h"

class User
{
	std::string public_key;
	std::string name;
	uint64_t balance;

public:
	User(std::string, uint64_t);
	~User(){};
	std::ostream& operator<<(std::ostream& os);
};