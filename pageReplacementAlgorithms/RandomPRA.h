#pragma once

#include "../PageReplacementAlgorithm.h"
#include <vector>


class RandomPRA : public PageReplacementAlgorithm
{

private:
	std::vector<int> pages;

public:
	RandomPRA() : PageReplacementAlgorithm() { }
	virtual ~RandomPRA() { }

	virtual int findVirtualPageToEvict(TableEntry *pageTable) override;
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) override;
};
