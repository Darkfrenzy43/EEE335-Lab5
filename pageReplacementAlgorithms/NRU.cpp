


#include "NRU.h"
#include <stdio.h>


// --- Declaration of Helper Functions in here to be explicit ---
void printPageTable(TableEntry* pageTable);




int NRU::findVirtualPageToEvict(TableEntry *pageTable)
{



	TableEntry* temp_ptr = pageTable; 





	return 0;


}

void NRU::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{

	printf(">>>Virtual page has been evicted.\n");
}

void NRU::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{
	printf(">>> Virtual page has been loaded.\n");
}

void NRU::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{
	printf(">>> Virtual page has been accessed.\n");
}
