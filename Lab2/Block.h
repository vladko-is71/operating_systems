#include <vector>
#pragma once
using namespace std;

class Page;

class Block
{
public:
	char* content;
	vector<Page> references;
	size_t memory_size;
	Block(vector<Page>, size_t);
	void find_page(vector<Page>);

private:
	size_t round_up(size_t);
};

