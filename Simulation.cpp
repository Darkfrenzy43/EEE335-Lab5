#include "Simulation.h"
#include "config.h"
#include "SimulationView.h"
#include "pageReplacementAlgorithms/Clock.h"
#include "pageReplacementAlgorithms/FIFO.h"
#include "pageReplacementAlgorithms/NRU.h"
#include "pageReplacementAlgorithms/RandomPRA.h"
#include "pageReplacementAlgorithms/SecondChance.h"
#include "pageReplacementAlgorithms/WorkingSet.h"
#include <chrono>
#include <cstdlib>
#include <thread>



Simulation::Simulation(SimulationView *view, std::string praText) : view(view)
{
	pageTable = (TableEntry*)malloc(NUM_VPAGES * sizeof(TableEntry));
	reversePageTable = (ReverseTableEntry*)malloc(NUM_VPAGES * sizeof(ReverseTableEntry));
	resetPageTable();
	resetReversePageTable();
	buildWorkingSet();
	createPra(praText);
}


Simulation::~Simulation()
{
	free(pageTable);
	free(reversePageTable);
	delete pra;
}


void Simulation::doTurn()
{
	int addressRef;
	int pageRef;


	// 1. Select the virtual page to be accessed
	// The page selected is not in the process working set
	if (rand()%100 < PROB_NOT_IN_WORKING_SET)
	{
		// Removes a page from the working set.
		workingSet.erase(workingSet.begin());

		// And adds a new page.
		pageRef = createNewWSRef();
		workingSet.push_back(pageRef);
	}
	// The page selected is in the process working set
	else
	{
		pageRef = workingSet.at(std::rand()%workingSet.size());
	}
	addressRef = pageRef*PAGE_SIZE + std::rand()%PAGE_SIZE;

	std::cout << "Turn " << turnCount << ": Process requests access to address " << addressRef << std::endl;
	std::cout << "    Retrieving virtual page " << pageRef << std::endl;


	// 2. If the pages is already in memory, do nothing
	// If the page is not in memory, check for an empty frame and load the page
	// If there are no empty frame, evict a page to create an empty frame and load the page

	// Page requested is in memory
	if (pageTable[pageRef].present)
	{
		;
	}

	// Page requested is not in memory
	else
	{
		faultCount++;
		std::cout << "    Page fault" << std::endl;

		// Find an empty frame in memory where the page can be loaded
		int availableFrame = -1;
		for (int i = 0; i < NUM_PFRAMES; i++)
		{
			if (reversePageTable[i].used == false)
			{
				availableFrame = i;
				std::cout << "    Frame " << i << " is free" << std::endl;
				break;
			}
		}

		// If there is no available frame, evict a page
		if (availableFrame == -1)
		{
			// Find the page to evict using the PageReplacementAlgorithm
			int pageToEvict = pra->findVirtualPageToEvict(pageTable);
			std::cout << "    Will evict page " << pageToEvict << std::endl;
			if (!isLoaded(pageToEvict))
			{
				std::cout << "ERROR: virtual page " << pageToEvict << " is not in memory" << std::endl;
				std::cout << "Exit in 5 seconds" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(5000));
				exit(-1);
			}

			// Evict the page
			std::cout << "    Page " << pageToEvict << " is evicted and saved to disk" << std::endl;
			availableFrame = pageTable[pageToEvict].physicalPage;
			reversePageTable[availableFrame].virtualPage = -1;
			reversePageTable[availableFrame].used = false;
			pageTable[pageToEvict].physicalPage = -1;
			pageTable[pageToEvict].present = false;
			pageTable[pageToEvict].used = false;
			pageTable[pageToEvict].dirty = false;
			pageTable[pageToEvict].timeLastUsed = 0;
			pra->virtualPageEvicted(pageTable, pageToEvict);
		}

		// Load the page into the available frame
		reversePageTable[availableFrame].virtualPage = pageRef;
		reversePageTable[availableFrame].used = true;
		pageTable[pageRef].physicalPage = availableFrame;
		pageTable[pageRef].present = true;
		pageTable[pageRef].used = true;
		//pageTable[pageRef].dirty = false;			// commented on purpose to let the PRA update this info
		//pageTable[pageRef].timeLastUsed = 0;		// commented on purpose to let the PRA update this info
		pra->virtualPageLoaded(pageTable, pageRef);
		std::cout << "    Page " << pageRef << " is loaded in frame " << availableFrame << std::endl;
	}


	// 3. Access the virtual page
	std::cout << "    Page " << pageRef << " is located in frame " << pageTable[pageRef].physicalPage << std::endl;
	bool modified = rand()%100 < PROB_PAGE_MODIFIED;
	pra->virtualPageAccessed(pageTable, pageRef, modified);
	int physicalAddress = pageTable[pageRef].physicalPage*PAGE_SIZE + addressRef%PAGE_SIZE;
	if (modified)
		std::cout << "    Physical address " << physicalAddress << " is accessed (read and write)" << std::endl;
	else
		std::cout << "    Physical address " << physicalAddress << " is accessed (read only)" << std::endl;
	std::cout << "\n...................................................\n" << std::endl;


	// Increase the count and update the GUI
	turnCount++;
	view->updateGUI();
	if (turnCount >= view->runFor)
		view->simulationComplete();
}


void Simulation::setPra(std::string praText)
{
	delete pra;
	createPra(praText);
}

void Simulation::createPra(std::string praText)
{
	if (praText.compare("Random") == 0)
		pra = new RandomPRA();
	else if (praText.compare("FIFO") == 0)
		pra = new FIFO();
	else if (praText.compare("Second Chance") == 0)
			pra = new SecondChance();
	else if (praText.compare("Clock") == 0)
			pra = new Clock();
	else if (praText.compare("NRU") == 0)
			pra = new NRU();
	else if (praText.compare("Working Set") == 0)
			pra = new WorkingSet();
	else
		pra = new RandomPRA();
}


void Simulation::resetPageTable()
{
	for (int i = 0; i < NUM_VPAGES; i++)
	{
		pageTable[i].physicalPage = -1;
		pageTable[i].present = false;
		pageTable[i].used = false;
		pageTable[i].dirty = false;
		pageTable[i].timeLastUsed = 0;
	}
}


void Simulation::resetReversePageTable()
{
	for (int i = 0; i < NUM_PFRAMES; i++)
	{
		reversePageTable[i].virtualPage = -1;
		reversePageTable[i].used = false;
	}
}


void Simulation::buildWorkingSet()
{
	workingSet.clear();
	for (int i = 0; i < WORKING_SET_SIZE; i++)
		workingSet.push_back(createNewWSRef());
}


int Simulation::createNewWSRef()
{
	int workingSetElement = rand()%NUM_VPAGES;

	if (workingSet.empty())
		return workingSetElement;
	else
	{
		while (isInWS(workingSetElement))
			workingSetElement = rand()%NUM_VPAGES;
		return workingSetElement;
	}
}


bool Simulation::isInWS(int page)
{
	for (auto i : workingSet)
	{
		if (i == page)
			return true;
	}
	return false;
}


bool Simulation::isLoaded(int page)
{
	for (int i = 0; i < NUM_PFRAMES; i++)
	{
		if (reversePageTable[i].virtualPage == page)
			return true;
	}
	return false;
}

