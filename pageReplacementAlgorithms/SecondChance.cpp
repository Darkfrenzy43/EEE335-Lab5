/*
	Description:

		Implementation of the Second Chance page table algorithm.


	Notes:

		- I've added a printer helper function just to help me out debug in here.
		Turns out,  all other  files in the pageReplacementAlgorithms/ directory can 
		also see the defined function, so that's rather convenient :/. 


	Author: OCdt Liethan Velasco
	
*/




#include "SecondChance.h"


// --- Declaration of Helper Functions ---


/* 
	Description:

		A helper function used in debugging. Simply iterates through the page table contents
		and print the information pertaining to each virtual page in the virtual memory.

	Arguments:
		<TableEntry* pageTable> : The pointer to the page table array used in the simulation.

*/
void printPageTable(TableEntry* pageTable) {

	// Printing out table's contents for debugging
	TableEntry* table_ptr = pageTable;
	for (int i = 0; i < NUM_VPAGES; i++) {

		// Extracting info
		int phys_num = table_ptr -> physicalPage;
		int used_bit =  table_ptr -> used;
		int pres_bit =  table_ptr -> present;
		int dirty_bit = table_ptr -> dirty;

		// Print info for the given virtual page
		printf("Virt page %3d: physical page  =  %2d; used = %d; present = %d; dirty = %d.\n", i, phys_num, used_bit, pres_bit, dirty_bit);

		// Increment to next virtual page
		table_ptr++;
	}

}



// --- Inherited  functions to implement ---

int SecondChance::findVirtualPageToEvict(TableEntry *pageTable)
{
	
	// Enter while loop to find page to evict
	while (true) {
		
		// Check if queue is not empty. If it is (which should never be), return 0 by deafult
		if (page_queue.size() == 0) {
			printf(">>> ERROR: FIFO queue is empty.\n");
			return 0;
		}

		// Otherwise, pop out first page in queue
		int evict_virtpage_num = page_queue.front();
		page_queue.pop();

		// Acquire in page table the virtual page whose number was popped 
		TableEntry* table_ptr = pageTable;
		for (int i = 0; i < evict_virtpage_num; i++) {
			table_ptr++;
		}

		// Check if popped virtual page is recently used (used = 1). If so, put at back of 
		// page queue and restart loop to get next one. If not, this is the page to evict.
		if (table_ptr -> used) {
			table_ptr -> used = 0;
			printf(">>> Virt page #%d is recently used. Used bit cleared and skipping.\n", evict_virtpage_num);
			page_queue.push(evict_virtpage_num);
			continue;
		}
		else {
			printf(">>> Virt page #%d not being used. Will be evicted.\n", evict_virtpage_num);
			return evict_virtpage_num;
		}

	}

}

void SecondChance::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{

}

void SecondChance::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{

	// Loading queue with page number to load
	page_queue.push(virtualPage);

}

void SecondChance::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{

	// Set the used bit of the accessed page to 1
	TableEntry* table_ptr = pageTable;
	for (int i = 0; i < virtualPage; i++) {
		table_ptr++;
	}
	table_ptr -> used = 1;

	// Printing page table for debugging
	printPageTable(pageTable);

}


