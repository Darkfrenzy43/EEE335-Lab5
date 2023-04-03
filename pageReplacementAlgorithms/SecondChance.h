#pragma once

#include "../PageReplacementAlgorithm.h"
#include "../config.h"
#include <stdio.h>
#include <queue>


using namespace std;

class SecondChance : public PageReplacementAlgorithm
{

private:

	// Creating the queue for Second Chance algo
	queue<int> page_queue;



public:
	SecondChance() : PageReplacementAlgorithm() { }
	virtual ~SecondChance() { }

	virtual int findVirtualPageToEvict(TableEntry *pageTable) override;
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) override;
};
