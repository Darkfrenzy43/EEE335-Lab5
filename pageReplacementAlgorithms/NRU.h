#pragma once

#include "../PageReplacementAlgorithm.h"
#include "../config.h"
#include <stdio.h>
#include <cstdlib>



class NRU : public PageReplacementAlgorithm
{

private:

	// Make four int arrays for each class for the algo. Make all max size NUM_PFRAMES
	int class_0[NUM_PFRAMES];
	int class_1[NUM_PFRAMES];
	int class_2[NUM_PFRAMES];
	int class_3[NUM_PFRAMES];

	// Make counters to track element count for each
	int count_0 = 0;
	int count_1 = 0;
	int count_2 = 0;
	int count_3 = 0;

	// Create a counter to handle clock interrupts, and a constant marking
	// after how many steps should a clock interrupt occur.
	int inter_count = 0;
	const int CLK_INT = 4;



public:
	NRU() : PageReplacementAlgorithm() { }
	virtual ~NRU() { }

	virtual int findVirtualPageToEvict(TableEntry *pageTable) override;
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) override;
};
