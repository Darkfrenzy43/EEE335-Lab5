/*

	Description:

		Implementation of the Clock page table algorithm.

		We'll create an array that represents the current pages
		in the RAM at any point. This is what we'll iterate through
		like a clock to find the next page to evict

	
	Notes:

		- seems like we have to just re-declare the prototype of the printPageTable() 
		helper function from SecondChance.cpp. Oh well. 

		- yeah it's supposed to work exactly like Second Chance, but this time
		we're going to use an array that does wrapping and all.

	
	Author: OCdt Liethan Velasco

*/



#include "Clock.h"


// --- Declaration of Helper Functions in here to be explicit ---
void printPageTable(TableEntry* pageTable);



int Clock::findVirtualPageToEvict(TableEntry *pageTable)
{

	// Enter while loop to find page to evict in the clock
	while (true) {

		// Get the virt page number of the currently pointed to virt pg in the phys_frame clock
		int virt_page_num = phys_entry_clk[clock_hand];

		// Get the actual virtual page with number virt_page_num
		TableEntry* table_ptr = pageTable;
		for (int i = 0; i < virt_page_num; i++) {
			table_ptr++;
		}


		// Check if the acquired virt page is used (and is currently in the RAM, obviously). If so, clear used bit,
		// increment clock hand to point to next physical frame, and restart loop.
		// Otherwise, return page to be evicted
		if (table_ptr -> used)  {
			table_ptr -> used = 0;
			printf(">>> Virt page #%d is recently used. Used bit cleared and skipping.\n", virt_page_num);
			clock_hand = (clock_hand + 1) % NUM_PFRAMES;
			continue;
		}
		else {
			printf(">>> Virt page #%d not being used. Will be evicted.\n", virt_page_num);
			return virt_page_num;
		}

	}

}

void Clock::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{

	// Setting modified bit to 0 upon any page evict
	pageTable[virtualPage].dirty = 0;
}

void Clock::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{

	// Insert the new virtual page in the physical frame clock where the hand is currently pointing
	phys_entry_clk[clock_hand] = virtualPage;

	// Advance clock hand to next virtual page location
	clock_hand = (clock_hand + 1) % NUM_PFRAMES;

}

void Clock::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{

	// Setting used bit to 1, and modified bit to 1 if modified is true
	pageTable[virtualPage].used = 1;
	if (modified) {
		pageTable[virtualPage].dirty = 1;
	}

	// Printing page table for debugging
	printPageTable(pageTable);

}



