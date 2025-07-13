#pragma once
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Platform.h"

class GridManager
{
private:
	int cellsize;
	int gridwidth;

	unordered_map<int, vector<Platform>> gridmap;

	int Poskey(Vector2f pos);

public:
	GridManager(int cellsize, int gridwidth) : cellsize(cellsize), gridwidth(gridwidth) {}

	void Addplatform(Platform& platform);

	vector<Platform> Collidableplatform(Vector2f pos);



};

