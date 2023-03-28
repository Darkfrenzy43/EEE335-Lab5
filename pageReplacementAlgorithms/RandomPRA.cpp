#include "RandomPRA.h"
#include <assert.h>
#include <cstdlib>




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
}

void RandomPRA::virtualPageLoaded(TableEntry *pageTable, int virtualPage)
{
	// Append the virtual page number to the end of the list
	pages.push_back(virtualPage);
}

void RandomPRA::virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified)
{

}
