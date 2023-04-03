/*
	Description:

		Plan is to use a queue to keep track of oldest and newest pages.
		Obviously when a page evict happens, the page at the queue's front is removed.
		Any newly added virtual pages are placed at the end of the queue. 

	Notes:

		- Plan on using c++'s queue in std library

	Author: OCdt Liethan Velasco


*/


// --- Importing modules ---

#include "FIFO.h"
#include <stdio.h>


/* 
	Description:

		Helper function to print contents of queue.

	Arguments:
		{queue<int> in_queue} : the queue to have its contents printed.
*/
void printQueue(queue<int> in_queue) {
	
	// Make a copy of queue
	queue<int> queue_copy = in_queue;

	printf("[");
	for (int i = 0; i < queue_copy.size(); i++) {
		printf(" %d ", queue_copy.front());
		queue_copy.pop();
	}
	printf("]\n");
}


int FIFO::findVirtualPageToEvict(TableEntry *pageTable)
{

	// Check if queue is not empty. If it is (which should never be), return 0 by deafult
	if (page_queue.size() == 0) {
		printf(">>> ERROR: FIFO queue is empty.\n");
		return 0;
	}

	// Otherwise, pop out first page in queue and return number
	int evict_page = page_queue.front();
	page_queue.pop();
	printf(">>> FIFO: Found page #%d to evict.\n", evict_page);

	return evict_page;
}

void FIFO::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{
	printf(">>> FIFO: Page #%d was evicted.\n", virtualPage);
	printQueue(page_queue);
}

void FIFO::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{

	// Loading queue with page number to load
	page_queue.push(virtualPage);

	printf(">>> FIFO: Virtual page #%d loaded.\n", virtualPage);

	printQueue(page_queue);
}

void FIFO::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{
	printf(">>> FIFO: Virtual page accessed.\n");
	

}
