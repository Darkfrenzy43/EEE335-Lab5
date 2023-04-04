/* 
	Description:

		Implementation of the Working Set page replacement algorithm.

		We'll taking things slowly here just to make sure that everything is implemented correctly. 

	
	Notes:

		- First, we implement the updating of the page's time last used field

		- TODO Question: Are we supposed to collect all pages that are not in working set, and choose randomly which one should be removed?

		Status:
			- change how page fault handled (find first one, remove. If non found, remove largest. If all same, return random).

	
	Author: OCdt Liethan Velasco

*/



#include "WorkingSet.h"



// --- Declaring modified version of helper function ---

/* 
	Description:

		A helper function used in debugging. Simply iterates through the page table contents
		and print the information pertaining to each virtual page in the virtual memory.

		Second iteration of the helper function which  also prints the time last used time

	Arguments:
		<TableEntry* pageTable> : The pointer to the page table array used in the simulation.

*/
void printPageTable2(TableEntry* pageTable) {

	// Printing out table's contents for debugging
	TableEntry* table_ptr = pageTable;
	for (int i = 0; i < NUM_VPAGES; i++) {

		// Extracting info
		int phys_num = table_ptr -> physicalPage;
		int used_bit =  table_ptr -> used;
		int pres_bit =  table_ptr -> present;
		int dirty_bit = table_ptr -> dirty;
		int time_last_used = table_ptr -> timeLastUsed;

		// Print info for the given virtual page
		printf("Virt page %3d: physical page  =  %2d; used = %d; present = %d; dirty = %d; time last used = %3d.\n", i, phys_num, used_bit, pres_bit, dirty_bit, time_last_used);

		// Increment to next virtual page
		table_ptr++;
	}

}


/*  TO BE DELETED - ONLY HELPER */
void  printNotWorkingSet(int in_arr[NUM_PFRAMES]) {

	printf(">>> Not in Working Set: [");
	for (int i = 0; i < NUM_PFRAMES; i++) {
		printf(" %d ", in_arr[i]);
	}
	printf("]\n");

}



int WorkingSet::findVirtualPageToEvict(TableEntry *pageTable)
{

	printf("Current virtual time = %d.\n", curr_virt_time);

	// Create temp vars to find the oldest page (in case all pages were used or were in working set)
	int oldest_page_age = 0;
	int oldest_page = -1;
	
	// Inspect each entry in RAM...
	for (int i = 0; i < NUM_VPAGES; i++) {

		// Skip the non-loaded pages
		if (pageTable[i].physicalPage == -1) {
			continue;
		}


		// If not, calculate age of page
		int age = curr_virt_time - (pageTable[i].timeLastUsed);
		printf("Age of %d: %d\n", i, age);		

		// check if current page has used bit = 1. If so, clear it, and update its time last used
		if (pageTable[i].used == 1) {
			printf("Page %d used bit cleared - time last used updated to %d.\n", i, curr_virt_time);
			pageTable[i].used = 0;
			pageTable[i].timeLastUsed = curr_virt_time;
		}
		else {

			// Update oldest page as applicable
			if (age > oldest_page_age) {
				oldest_page_age = age;
				oldest_page = i;
			}	

			// Otherwise, check if the age makes it out of working set. If not, this is page to evict
			if (age > WS_WINDOW) {
				printf("Page %d is not in working set. Returning this to be evicted.\n", i);
				return i;
			}

		}

	}


	// Creating a dummy array to contain the loaded pages
	int loaded_pg_arr[NUM_PFRAMES];
	int loaded_pg_counter = 0;

	// Arrived here if all pages were in working set. 
	// First, find the first page that is loaded, capture its time last used
	int temp;
	for (int i = 0; i < NUM_VPAGES; i++) {
		
		// skip non loaded pages
		if (pageTable[i].physicalPage == -1) {
			continue;
		}
		
		temp = pageTable[i].timeLastUsed;

	}

	// Quickly look through all the loaded pages and determine if all have same last time used value. 
	bool different = false;
	for (int i = 0; i < NUM_VPAGES; i++) {

		// skip non loaded pages
		if (pageTable[i].physicalPage == -1) {
			continue;
		}

		// Load current page into dummy array for later
		loaded_pg_arr[loaded_pg_counter++] = i;

		// Check if current val was ever different from prev value. 
		if (temp != pageTable[i].timeLastUsed) {
			different = true;
		}

	}

	printNotWorkingSet(loaded_pg_arr);

	// If oldest_page = -1, means all pages were referenced before page fault and subsequenlty updated. If so, return a page randomly.
	if (oldest_page == -1) {
		int rand_ind = rand() % NUM_PFRAMES;
		printf(">>> All pages were updated in page fault. Returning randomly page %d.\n", loaded_pg_arr[rand_ind]);
		return loaded_pg_arr[rand_ind];
	}

	// If  there were different pages, return oldest found page. 
	// Otherwise, return random loaded page among them. 
	if (different) {

		printf(">>> Not all pages in working set are same. Returning oldest page of #%d.\n", oldest_page);
		return oldest_page;
		
	}
	else {

		int rand_ind = rand() % NUM_PFRAMES;
		printf(">>> All times of pages are equal. Returning randomly page %d.\n", loaded_pg_arr[rand_ind]);
		return loaded_pg_arr[rand_ind];

	}

}


void WorkingSet::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{

	printf(">>> Evicting page %d.\n", virtualPage);

	// For any evicted page, always ensure its modified bit is cleared
	pageTable[virtualPage].dirty = 0;

}

void WorkingSet::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{

}

void WorkingSet::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{

	// Every page reference, increment virtual time
	curr_virt_time++;

	// Set the used bit of the accessed page to 1
	pageTable[virtualPage].used = 1;
                    
	// Set the modified bit to 1 if modified argument is true (although this one doesn't matter as much)
	if (modified) {
		pageTable[virtualPage].dirty = 1;
	}
	
	// Every time a virtual page is accessed, increase program step counter var.
	// If program counter var reaches clock tick constant value, simulate a clock tick
	prog_steps++;
	if (prog_steps == CLK_TICK) {

		printf(">>> CLOCK TICK INTERRUPT\n");

		// Reset step counter
		prog_steps = 0;

		// Loop through all pages
		for (int i = 0; i < NUM_VPAGES; i++) {

			// If not page not in memory, skip
			if (pageTable[i].physicalPage == -1) {
				continue;
			}

			// If used bit of page is 1, clear it and set its time last used field to val of curr_virt_time
			if (pageTable[i].used == 1) {

				printf("Page %d: used = 1; time last used field updated to %d.\n", i, curr_virt_time);
				pageTable[i].used = 0;
				pageTable[i].timeLastUsed = curr_virt_time;

			}

		}
		
	}


	// Print page table here for debugging
	printPageTable2(pageTable);

}
