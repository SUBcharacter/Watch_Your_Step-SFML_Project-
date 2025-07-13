#pragma once
#include "IntegrationLibrary.h"

struct PairHash
{
	size_t operator()(const pair<int, int>& p) const
	{
		return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
	}
};

struct Platform {};

class Grid
{
private:
	int cellSize = 100;
	unordered_map<pair<int, int>, vector<Platform*>, PairHash> gridCells;

public:
	Grid();
};

