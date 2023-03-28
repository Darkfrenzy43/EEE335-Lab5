#pragma once


#define NUM_VPAGES 16						// Number of virtual page (process address space)
#define NUM_PFRAMES 8						// Number of physical frames (RAM size)
#define PAGE_SIZE 4096						// Size of pages and frames

#define WORKING_SET_SIZE 6					// Number of pages in the process working set (used for the simulation)
#define PROB_NOT_IN_WORKING_SET 25			// in %, probability that the page requested is not in the working set
#define PROB_PAGE_MODIFIED 25 				// in %, probability that the page requested is modified (written to)

#define NORMAL_DELAY 500					// in milliseconds, delay between steps
#define FAST_DELAY 100						// in milliseconds, delay between steps
#define TURBO_DELAY 1						// in milliseconds, delay between steps
#define DEFAULT_SPEED "Turbo"				// Select between "Normal", "Fast" or "Turbo"

#define RUN_FOR_CHOICE_1 1000				// Number of steps, one of the three options in the "Run for" drop-down menu
#define RUN_FOR_CHOICE_2 5000				// Number of steps, one of the three options in the "Run for" drop-down menu
#define RUN_FOR_CHOICE_3 10000				// Number of steps, one of the three options in the "Run for" drop-down menu
#define DEFAULT_RUN_FOR RUN_FOR_CHOICE_2	// Default option in the "Run for" drop-down menu

#define HIGHLIGHT_COLOR_FONT "black"		// Font color used to highlight a change in the page table
#define HIGHLIGHT_COLOR_BG "yellow"			// Background color used to highlight a change in the page table
