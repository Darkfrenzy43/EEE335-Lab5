#pragma once

#include "../PageReplacementAlgorithm.h"
#include "../config.h"
#include <stdio.h>


using namespace std;


class Clock : public PageReplacementAlgorithm
{

private:

	// Create a "clock hand" var that iterates through the virt pages in the page table
	int clock_hand = 0;

	// Create an array for each page entry in the RAM
	int phys_entry_clk[NUM_PFRAMES];


public:
	Clock() : PageReplacementAlgorithm() { }
	virtual ~Clock() { }

	virtual int findVirtualPageToEvict(TableEntry *pageTable) override;
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) override;
};
