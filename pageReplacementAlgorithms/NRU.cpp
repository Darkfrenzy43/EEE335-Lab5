#include "NRU.h"
#include <stdio.h>



int NRU::findVirtualPageToEvict(TableEntry *pageTable)
{

	printf("This happened.\n");

	TableEntry* temp_ptr = pageTable; 

	// Loop through all the page frames and categorize each in their classes
	for (int i = 0; i < pages.size(); i++) {
		
		printf("Page %d: Reference bit = %d, Modify bit = %d\n", i, temp_ptr -> used, temp_ptr -> dirty);
		temp_ptr++;
		
	}
	// Find a random page in the lowest class to evict
	

	return 0;


}

void NRU::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{

	printf("Virtual page has been evicted.\n");
}

void NRU::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{
	printf("Virtual page has been loaded.\n");
}

void NRU::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{

}
