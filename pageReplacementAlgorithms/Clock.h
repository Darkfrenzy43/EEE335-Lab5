#pragma once

#include "../PageReplacementAlgorithm.h"


class Clock : public PageReplacementAlgorithm
{

private:


public:
	Clock() : PageReplacementAlgorithm() { }
	virtual ~Clock() { }

	virtual int findVirtualPageToEvict(TableEntry *pageTable) override;
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) override;
};
