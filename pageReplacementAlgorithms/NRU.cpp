/*
	Description:

		Implementation of the Not Recently Used page replacement algorithm.

		The easiest method I came up with is just using four different
		arrays to store the virtual pages currently loaded in RAM in the four possible classes.

		I did not want to use vectors because I am certainly far more comfortable using arrays.

	
	Notes:

		- We are using a counter that keeps track of when to call a clock interrupt. We will
		be setting it to incur an interrupt every 8 steps. Why 8? Because why not. (Not planning
		on tuning this value to find the optimum clear time.  Maybe. We'll see.)

	
	Author: OCdt Liethan Velasco


*/


#include "NRU.h"


// --- Declaration of Helper Functions in here to be explicit ---
void printPageTable(TableEntry* pageTable);


void  printArray(int in_arr[NUM_PFRAMES], int  class_num) {

	printf(">>> Class %d: [", class_num);
	for (int i = 0; i < NUM_PFRAMES; i++) {
		printf(" %d ", in_arr[i]);
	}
	printf("]\n");

}



int NRU::findVirtualPageToEvict(TableEntry *pageTable)
{

	// Set all the entries in the class arrays to -1 to start
	for (int i = 0; i < NUM_PFRAMES; i++) {
		class_0[i] = -1;
		class_1[i] = -1;
		class_2[i] = -1;
		class_3[i] = -1;
	}

	// Reset all the array counters
	count_0 = 0;
	count_1 = 0;
	count_2 = 0;
	count_3 = 0;

	// Iterate through the virtual pages in page table...
	TableEntry* table_ptr = pageTable;
	for (int i = 0; i < NUM_VPAGES; i++) {

		// Check if physical frame field = -1. If it is, means not loaded in RAM - skip it
		if (table_ptr -> physicalPage == -1) {
			table_ptr++;
			continue;
		}

		// Otherwise, categorize the current virtual page in 
		// the appropriate class depending on the page's current fields
		bool ref_bit = table_ptr -> used;
		bool mod_bit = table_ptr -> dirty;
		if (!ref_bit && !mod_bit) {
			class_0[count_0] = i;
			count_0++;
		}
		else if (!ref_bit && mod_bit) {
			class_1[count_1] = i;
			count_1++;
		}
		else if (ref_bit && !mod_bit) {
			class_2[count_2] = i;
			count_2++;
		}
		else {
			class_3[count_3] = i;
			count_3++;
		}

		table_ptr++;

	}


	// For now, print contents of arrays
	printArray(class_0, 0);
	printArray(class_1, 1);
	printArray(class_2, 2);
	printArray(class_3, 3);

	// According to algorithm, return a random virtual page in the lowest class
	int rand_ind;
	if (count_0 != 0) {
		rand_ind = rand() % count_0;
		printf(">>> Returning page %d at rand_ind %d from class 0 to evict.\n", class_0[rand_ind], rand_ind);
		return class_0[rand_ind];
	}
	else if (count_1 != 0) {
		rand_ind = rand() % count_1;
		printf(">>> Returning page %d at rand_ind %d from class 1 to evict.\n", class_1[rand_ind], rand_ind);
		return class_1[rand_ind];
	}
	else if (count_2 !=  0) {
		rand_ind = rand() % count_2;
		printf(">>> Returning page %d at rand_ind %d from class 2 to evict.\n", class_2[rand_ind], rand_ind);
		return class_2[rand_ind];
	}
	else {
		rand_ind = rand() % count_3;
		printf(">>> Returning page %d at rand_ind %d from class 3 to evict.\n", class_3[rand_ind], rand_ind);
		return class_3[rand_ind];
	}



	return 0;


}

void NRU::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{

	printf(">>> Virtual page %d evicted. Dirty bit cleared.\n", virtualPage);

	// For any evicted page, always ensure its modified bit is cleared
	TableEntry* table_ptr = pageTable;
	for (int i = 0; i < virtualPage; i++) {
		table_ptr++;
	}
	table_ptr -> dirty = 0;	

}

void NRU::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{
	printf(">>> Virtual page has been loaded.\n");
}

void NRU::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{
	
	// Set the used bit of the accessed page to 1
	TableEntry* table_ptr = pageTable;
	for (int i = 0; i < virtualPage; i++) {
		table_ptr++;
	}
	table_ptr -> used = 1;

	// Set the modified bit to 1 if modified argument is true
	if (modified) {
		table_ptr -> dirty = 1;
	}

	// Increment step counter for interrupts. If reached interrupt value, 
	// incur interrupt (clear all the reference bits in vpages) and reset counter.
	if (inter_count == CLK_INT) {

		printf(">>> CLOCK INTERRUPT: Clearing all used bits.\n");
		
		inter_count = 0;
		
		TableEntry* table_ptr = pageTable;
		for (int i = 0; i < NUM_VPAGES; i++) {
			table_ptr -> used = 0;
			table_ptr++;
		}
	}
	else {

		inter_count++;

	}

	printPageTable(pageTable);
}
