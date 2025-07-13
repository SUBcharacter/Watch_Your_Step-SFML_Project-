#include "Grid.h"

Grid::Grid(float size)
{
	cellSize = size;
}

void Grid::RegisterPlatform(Platform* p)
{
	p->UpdateHitBox();
	FloatRect box = p->GetHitBox();

	int startX = static_cast<int>(floor(box.position.x / cellSize));
	int endX = static_cast<int>(floor((box.position.x + box.size.x) / cellSize));
	int startY = static_cast<int>(floor(box.position.y / cellSize));
	int endY = static_cast<int>(floor((box.position.y + box.size.y) / cellSize));

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
		}
	}
}
