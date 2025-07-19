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
	GameManager(Player& p ) :player(p), grid(100.f), collider(player) {}

	void Init();
	void Update(PlatformType type,float deltaTime);
	void Draw(RenderWindow& window);

};

