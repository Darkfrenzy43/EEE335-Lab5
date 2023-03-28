#pragma once


struct TableEntry {
	int physicalPage = -1;
	bool present = false;
	bool used = false;
	bool dirty = false;
	int timeLastUsed = 0;
};

struct ReverseTableEntry {
	int virtualPage = -1;
	bool used = false;
};