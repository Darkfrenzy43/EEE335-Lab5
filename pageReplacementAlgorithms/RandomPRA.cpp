#include "RandomPRA.h"
#include <assert.h>
#include <cstdlib>
#include <stdio.h>




int RandomPRA::findVirtualPageToEvict(TableEntry *pageTable)
{
	// Find a random index in the list of loaded pages
	int temp = std::rand()%pages.size();

	// Find the number at that index
	int pageNumber = pages.at(temp);

	// Return the number of the virtual page to be evicted
	return pageNumber;
}

void RandomPRA::virtualPageEvicted(TableEntry *pageTable, int virtualPage)
{
	// Find the index of the virtual page in the vector of loaded pages
	int index = -1;
	for (int i = 0; i < pages.size(); i++)
	{
		if (pages.at(i) == virtualPage)
			index = i;
	}
	assert(index != -1);

	// Remove the evicted page from the list of loaded pages
	pages.erase(pages.begin() + index);



	printf(">>> Random: Page #%d at index %d was evicted.\n", virtualPage, index);
}

void RandomPRA::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{
	// Append the virtual page number to the end of the list
	pages.push_back(virtualPage);
}

void RandomPRA::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{

	printf(">>> Number of current pages is: %d.\n", pages.size());


	// --------- Reverse engineering the API -------------

	printf(">>> Number of current pages is: %d.\n", pages.size());

	// Let's try to print this page table contents first
	TableEntry* table_ptr = pageTable;

	printf("The physical page is currently %d.\n", table_ptr -> physicalPage); 
	// Above gives -1 always. I think this value we change. 

}
