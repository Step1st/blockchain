#include "Block.h"

Block::Block()
{
	timestamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	version = VERSION;
}
