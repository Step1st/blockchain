#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>

#include "Pool.h"
#include "Transaction.h"
#include "Block.h"
#include "hash.h"
#include "User.h"

void generateUsers(std::vector<User>& users);
void generatePool(Pool& pool);

int main() {
	std::vector<User> users;
	Pool pool;
	generateUsers(users);
	generatePool(pool);

	return 0;
}

void generateUsers(std::vector<User>& users) {
	std::mt19937 generator(1);
	std::uniform_int_distribution<uint64_t> distribution(1000, 100000);
	std::ofstream output("user_begin.txt");
	std::stringstream ofbuf;

	for (size_t i = 0; i < 1000; i++)
	{
		User temp("user" + std::to_string(i + 1), distribution(generator));
		temp << output;
		output << "----------------------------------------\n";

		users.push_back(temp);
	}
}

void generatePool(Pool& pool) {
	Transaction temp;
}