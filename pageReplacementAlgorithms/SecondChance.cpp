#include "SecondChance.h"
#include <stdio.h>



int SecondChance::findVirtualPageToEvict(TableEntry *pageTable)
{
	
		// Check if queue is not empty. If it is (which should never be), return 0 by deafult
	if (page_queue.size() == 0) {
		printf(">>> ERROR: FIFO queue is empty.\n");
		return 0;
	}

	// Otherwise, pop out first page in queue and return number
	int evict_page = page_queue.front();
	page_queue.pop();

	// Get the page in the page table, check if gets second chance
	// todo - figure out how to access the page table. It's done with pointers as far as I know. 

	// printf(">>> Second Chance: Found page #%d to evict.\n", evict_page);


	return evict_page;
}

void SecondChance::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{

	// Loading queue with page number to load
	// page_queue.push(virtualPage);


	// // Find the index of the virtual page in the vector of loaded pages
	// int index = -1;
	// for (int i = 0; i < pages.size(); i++)
	// {
	// 	if (pages.at(i) == virtualPage)
	// 		index = i;
	// }

	// // Remove the evicted page from the list of loaded pages
	// pages.erase(pages.begin() + index);


	printf(">>> Second Chance: Page #%d at index was evicted.\n", virtualPage);

}

void SecondChance::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{

	// Loading queue with page number to load
	page_queue.push(virtualPage);

	// Append the virtual page number to end of vector list
	// pages.push_back(virtualPage);

	printf(">>> Second Chance: Virtual page #%d loaded.\n", virtualPage);

}

void SecondChance::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{

	printf(">>> Second Chance: Virtual page accessed.\n");

	printf(">>> Number of current pages is: %d.\n", page_queue.size());

	// Let's try to print this page table contents first
	TableEntry* table_ptr = pageTable;

	for (int i = 0; i < page_queue.size(); i++) {

		int used_bit;
		if (table_ptr -> used) {
			used_bit = 1;
		}
		else {
			used_bit = 0;
		}

		printf("Iter %d: physical page is %d, time last used is %d. Used bit = %d\n", i, table_ptr -> physicalPage, table_ptr -> timeLastUsed, used_bit);
		table_ptr++;
	}


}
