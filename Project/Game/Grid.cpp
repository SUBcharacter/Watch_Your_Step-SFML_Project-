#include "Grid.h"


Grid::Grid()
{
}

void Grid::RegisterPlatform(Platform* p)
{
	p->UpdateHitBox();
	FloatRect box = p->GetHitBox();

	int startX = static_cast<int>(floor(box.position.x / cellSize));
	int endX = static_cast<int>(floor((box.position.x + box.size.x) / cellSize));
	int startY = static_cast<int>(floor(box.position.y / cellSize));
	int endY = static_cast<int>(floor((box.position.y + box.size.y) / cellSize));

	p->registeredCells.clear();

	for (int i = startY; i <= endY; i++)
	{
		for (int j = startX; j <= endX; j++)
		{
			pair<int, int> cell = { j, i };

			auto& platform = gridCells[cell];

			if (find(platform.begin(), platform.end(), p) == platform.end())
			{
				platform.push_back(p);
			}

			p->registeredCells.push_back(cell);
		}
	}
}

void Grid::UnregisterPlatform(Platform* p)
{
	for (const auto& cell : p->registeredCells)
	{
		auto it = gridCells.find(cell);
		if (it != gridCells.end())
		{
			auto& platformList = it->second;
			platformList.erase(remove(platformList.begin(), platformList.end(), p), platformList.end());

			if (platformList.empty())
			{
				gridCells.erase(it);
			}
		}
	}

	p->registeredCells.clear();
}

vector<Platform*> Grid::nearByPlayerPlatform(const vector<pair<int, int>>& gridCoord)
{
	unordered_set<Platform*> uniquePlatform;

	for (const auto& coord : gridCoord)
	{
		auto it = gridCells.find(coord);

		if (it != gridCells.end())
		{
			for (Platform* p : it->second)
			{
				uniquePlatform.insert(p);
			}
		}
	}
	return vector<Platform*>(uniquePlatform.begin(),uniquePlatform.end());
}
