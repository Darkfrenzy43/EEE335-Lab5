#pragma once

#include "PageTableEntry.h"


class PageReplacementAlgorithm
{

public:
	PageReplacementAlgorithm() { }
	virtual ~PageReplacementAlgorithm() { }

	// Returns the number of the virtual page to evict
	virtual int findVirtualPageToEvict(TableEntry *pageTable) = 0;

	// Notifies the PRA that a virtual page was evicted from memory
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) = 0;

	// Notifies the PRA that a virtual page was loaded in memory
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) = 0;

	// Notifies the PRA that a virtual page was accessed
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) = 0;
};


