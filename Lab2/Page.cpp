#include "Block.h"
#include "Page.h"
using namespace std;

Page::Page(size_t size) {
	contents = vector<Block>();
	content_pointers = vector<char*>();
	free_memory = 4096;
	block_size = size;
}

// Adding the block to the page
void Page::add_block(Block block) {
	contents.push_back(block);
	content_pointers.push_back(block.content);
	free_memory -= block.memory_size;
}