#pragma once

#include "../PageReplacementAlgorithm.h"


class WorkingSet : public PageReplacementAlgorithm
{

private:


public:
	WorkingSet() : PageReplacementAlgorithm() { }
	virtual ~WorkingSet() { }

	virtual int findVirtualPageToEvict(TableEntry *pageTable) override;
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) override;
};
