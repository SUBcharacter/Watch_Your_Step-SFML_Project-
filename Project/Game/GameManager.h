#pragma once
#include "IntegrationLibrary.h"
#include "Collider.h"
#include "Grid.h"

class GameManager
{
private:
	Player& player;
	vector<Platform*> allPlatform;
	Grid grid;
	Collider collider;

public:
	GameManager();

};

