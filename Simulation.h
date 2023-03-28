#pragma once

#include "PageTableEntry.h"
#include "PageReplacementAlgorithm.h"
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

class PageTableEntry;
class SimulationView;


class Simulation
{
public:
	int turnCount = 0;
	int faultCount = 0;
	SimulationView *view;
	TableEntry *pageTable;
	ReverseTableEntry *reversePageTable;

public:
	Simulation(SimulationView *view, std::string praText);
	~Simulation();
	void setPra(std::string pra);
	void doTurn();

private:
	std::vector<int> workingSet;
	PageReplacementAlgorithm *pra;

	void createPra(std::string praText);
	void resetPageTable();
	void resetReversePageTable();
	void buildWorkingSet();
	int createNewWSRef();
	bool isInWS(int page);
	bool isLoaded(int page);
};
