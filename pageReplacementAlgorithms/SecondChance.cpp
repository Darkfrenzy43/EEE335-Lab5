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
	printf(">>> Second Chance: Found page #%d to evict.\n", evict_page);

	return evict_page;
}

void SecondChance::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{
	printf(">>> Second Chance: Page #%d was evicted.\n", virtualPage);

}

void SecondChance::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{
	// Loading queue with page number to load
	page_queue.push(virtualPage);

	printf(">>> Second Chance: Virtual page #%d loaded.\n", virtualPage);

}

void SecondChance::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{
	printf(">>> Second Chance: Virtual page accessed.\n");
}
