#pragma once
#include "IntegrationLibrary.h"
#include "Platform.h"
//#include "Player.h"

struct Player {};

class Collider
{
private:
	Player& p;
	
public:
	bool isColliding(const vector<Platform*> np);

};

