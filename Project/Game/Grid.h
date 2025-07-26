#pragma once
#include "IntegrationLibrary.h"
#include "Platform.h"

struct PairHash
{
	size_t operator()(const pair<int, int>& p) const
	{
		return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
	}
};

class Grid
{
private:
	const float cellSize = 100.f;
	unordered_map<pair<int, int>, vector<Platform*>, PairHash> gridCells;

public:
	Grid();

	void RegisterPlatform(Platform* p);

	void UnregisterPlatform(Platform* p);

	vector<Platform*> nearByPlayerPlatform(const vector<pair<int, int>>& gridCoord);

};

