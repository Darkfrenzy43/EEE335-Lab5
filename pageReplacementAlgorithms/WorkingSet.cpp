/* 
	Description:

		Implementation of the Working Set page replacement algorithm.

		We'll taking things slowly here just to make sure that everything is implemented correctly. 

	
	Notes:

		- First, we implement the updating of the page's time last used field

		- TODO Question: Are we supposed to collect all pages that are not in working set, and choose randomly which one should be removed?

	
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

	// Empty the not working set array, default values to -1
	for (int i = 0; i < NUM_PFRAMES; i++) {
		not_WS[i] = -1;
	}
	not_WS_count = 0;

	printf("Current virtual time = %d.\n", curr_virt_time);

	// Create temp vars to find the oldest page (in case all pages are currently in working set)
	int oldest_page_age = 0;
	int oldest_page;
	
	// Inspect each entry in RAM...
	TableEntry* table_ptr = pageTable;
	for (int i = 0; i < NUM_VPAGES; i++) {

		// Skip the non-loaded pages
		if (table_ptr -> physicalPage == -1) {
			table_ptr++;
			continue;
		}

		
		// Calculate age of page
		int age = curr_virt_time - (table_ptr -> timeLastUsed);
		printf("Age of %d: %d\n", i, age);

		// Update oldest page as applicable
		if (age > oldest_page_age) {
			oldest_page_age = age;
			oldest_page = i;
		}

		// Determine if page is not in working set. If not, add to array accordingly
		if (age > WS_WINDOW && table_ptr -> used == 0) {
			not_WS[not_WS_count] = i;
			not_WS_count++;
		}

		// Increment page table pointer
		table_ptr++;
	}

	// DEBUGGING: Print not working set for now
	printNotWorkingSet(not_WS);
	printf("Oldest page is found to be %d.\n", oldest_page);

	// If all pages are currently in working set, return oldest page to evict.
	// Otherwise, randomly choose a page in non working set to remove. 				<---- COULD CHANGE
	if (not_WS_count == 0) {
		printf(">>> No pages in WS. Returning oldest.\n");
		return oldest_page;
	}
	else {
		int rand_ind = rand() % not_WS_count;
		printf(">>> Randomly chosen page %d to be returned.\n", not_WS[rand_ind]);
		return not_WS[rand_ind];
	}

	return 0;

}

void WorkingSet::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{

	// For any evicted page, always ensure its modified bit is cleared
	TableEntry* table_ptr = pageTable;
	for (int i = 0; i < virtualPage; i++) {
		table_ptr++;
	}
	table_ptr -> dirty = 0;	

}

void WorkingSet::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{

}

void WorkingSet::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{

	// Set the used bit of the accessed page to 1
	TableEntry* table_ptr = pageTable;
	for (int i = 0; i < virtualPage; i++) {
		table_ptr++;
	}
	table_ptr -> used = 1;

	// Set the modified bit to 1 if modified argument is true (although this one doesn't matter as much)
	if (modified) {
		table_ptr -> dirty = 1;
	}

	// Increment current virtual time, and set accessed pages time last used field
	curr_virt_time++;
	table_ptr -> timeLastUsed = curr_virt_time;

	// Every time a virtual page is accessed, increase program step counter var.
	// If program counter var reaches clock tick constant value, simulate a clock tick
	prog_steps++;
	if (prog_steps == CLK_TICK) {

		printf(">>> CLOCK INTERRUPT: Clearing all used bits.\n");
		
		prog_steps = 0;
		
		table_ptr = pageTable;
		for (int i = 0; i < NUM_VPAGES; i++) {
			table_ptr -> used = 0;
			table_ptr++;
		}
	}


	// Print page table here for debugging
	printPageTable2(pageTable);

}
