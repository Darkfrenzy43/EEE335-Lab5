#pragma once

#include "../PageReplacementAlgorithm.h"


class FIFO : public PageReplacementAlgorithm
{

private:


public:
	FIFO() : PageReplacementAlgorithm() { }
	virtual ~FIFO() { }

	virtual int findVirtualPageToEvict(TableEntry *pageTable) override;
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) override;
};
