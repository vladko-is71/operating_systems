#include <iostream>
#include <cstring>
#pragma once

class Block;

class Page
{
public:
	vector<Block> contents;
	vector<char*> content_pointers;
	size_t free_memory;
	int block_size;
	Page(size_t);
	void add_block(Block);
};

