#pragma once

#include "../PageReplacementAlgorithm.h"
#include <vector>

class NRU : public PageReplacementAlgorithm
{

private:

	// Creating a vector of integers that are the page frames. 
	std::vector<int> pages;

public:
	NRU() : PageReplacementAlgorithm() { }
	virtual ~NRU() { }

	virtual int findVirtualPageToEvict(TableEntry *pageTable) override;
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) override;
};
