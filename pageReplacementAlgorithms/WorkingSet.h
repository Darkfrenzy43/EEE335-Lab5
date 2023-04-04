#pragma once

#include "../PageReplacementAlgorithm.h"
#include "../config.h"
#include <stdio.h>
#include <cstdlib>


class WorkingSet : public PageReplacementAlgorithm
{

private:

	// Create a counter variable that tracks the "current virtual time"
	int curr_virt_time = 0;

	// Create a counter var that tracks program steps executed
	int prog_steps = 0;

	// Create constant that tracks number of steps to call before clock tick occurs. Initialize to 7 cuz why not.
	const int CLK_TICK = 7;

	// Create constant to represent the clock tick working set window 
	const int WS_WINDOW = 10; 


public:
	WorkingSet() : PageReplacementAlgorithm() { }
	virtual ~WorkingSet() { }

	virtual int findVirtualPageToEvict(TableEntry *pageTable) override;
	virtual void virtualPageEvicted(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageLoaded(TableEntry *pageTable, int virtualPage) override;
	virtual void virtualPageAccessed(TableEntry *pageTable, int virtualPage, bool modified) override;
};
