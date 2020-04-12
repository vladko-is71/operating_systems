#include "Block.h"
#include "Page.h"
using namespace std;

Block::Block(vector<Page> all_pages, size_t size) {
	references = vector<Page>();
	memory_size = round_up(size);
	content = new char[memory_size];
	find_page(all_pages);
}

// Rounding up the size, so it could always be 2^n
size_t Block::round_up(size_t size) {
	int current_size = 2;
	while (true) {
		if (size >= current_size)
			return (size_t)current_size;
		current_size *= 2;
	}
}

// Finding the page to fit the block
// (It has to have enough free space,
// and the page should be divided into the blocks of the same size)
void Block::find_page(vector<Page> all_pages) {
	if (memory_size >= 4096) {
		int number_of_pages = memory_size / 4096;
		for (int i = 0; i < number_of_pages; i++) {
			Page new_page = Page(memory_size);
			new_page.add_block(*this);
			references.push_back(new_page);
			all_pages.push_back(new_page);
		}
	}
	else {
		int acceptable_page_index = -1;
		for (int i = 0; i < all_pages.size(); i++) {
			if (memory_size <= all_pages[i].free_memory && all_pages[i].block_size == memory_size) {
				acceptable_page_index = i;
				break;
			}
		}
		if (acceptable_page_index == -1) {
			Page new_page = Page(memory_size);
			new_page.add_block(*this);
			references.push_back(new_page);
			all_pages.push_back(new_page);
		}
		else {
			all_pages[acceptable_page_index].add_block(*this);
			references.push_back(all_pages[acceptable_page_index]);
		}
	}
}