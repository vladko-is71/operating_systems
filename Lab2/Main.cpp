#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <vector>
#include "Block.h"
#include "Page.h"

using namespace std;

vector<Page> pages;
vector<Block> blocks;

void* mem_alloc(size_t);
void* mem_realloc(void*, size_t);
void mem_free(void*, bool);
void mem_dump();


int main() {
	void* pointer = mem_alloc(2000);
	void* other_pointer = mem_alloc(128);
	void* reallocating = mem_realloc(pointer, 2048);
	void* one_more_pointer = mem_alloc(2048);
	mem_free(other_pointer, true);
	mem_free(reallocating, true);
	mem_free(one_more_pointer, true);
	mem_dump();
}

// Allocating memory
void* mem_alloc(size_t size) {
	Block new_memory = Block(pages, size);
	blocks.push_back(new_memory);
	cout << "Memory was allocated" << endl;
	mem_dump();
	return (void*)new_memory.content;
}

// Reallocating memory
void* mem_realloc(void* addr, size_t size) {
	Block alternative_memory = Block(pages, size);
	blocks.push_back(alternative_memory);
	char* address = (char*)addr;
	strcpy(alternative_memory.content, address);
	mem_free(addr, false);
	cout << "Memory was reallocated" << endl;
	mem_dump();
	return (void*)alternative_memory.content;
}

// Freeing memory: making sure the deleted memory is not mentioned anywhere
// (The second param is there because we don't need output
// when this function is part of reallocating the memory)
void mem_free(void* addr, bool with_output) {
	for (int i = 0; i < pages.size(); i++) {
		for (int j = 0; j < pages[i].contents.size(); j++) {
			if (pages[i].contents[j].content == (char*)addr) {
				pages[i].contents.erase(pages[i].contents.begin() + j);
				pages[i].content_pointers.erase(pages[i].content_pointers.begin() + j);
				break;
			}
		}
	}
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i].content == (char*)addr) {
			Block* to_be_deleted = &(blocks[i]);
			blocks.erase(blocks.begin() + i);
			break;
		}
	}
	if (with_output) {
		cout << "Memory was freed" << endl;
	}
}

// Outputting the memory statistics
void mem_dump() {
	cout << "Taken memory blocks:" << endl;
	if (blocks.size() != 0) {
		for (int i = 0; i < blocks.size(); i++) {
			cout << &blocks[i].content << endl;
		}
	}
	else {
		cout << "(none)" << endl;
	}
}