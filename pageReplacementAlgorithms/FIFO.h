#pragma once


// --- Importing needed modules and declaring namespaces ---

#include "../PageReplacementAlgorithm.h"
#include <queue>

using namespace std;


class FIFO : public PageReplacementAlgorithm
{

private:

	// Creating the queue for FIFO algo
	queue<int> page_queue;
	

public:
	FIFO() : PageReplacementAlgorithm() { }
	virtual ~FIFO() { }

	virtual int findVirtualPageToEvict(TableEntry *pageTable) override;
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) override;
};
