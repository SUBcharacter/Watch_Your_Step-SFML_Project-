#pragma once
#include "IntegrationLibrary.h"

class Physics
{
private:

	float Yspeed = 0.0f;
	float gravity = 0.5f;
	bool fall = true;
public:
	int playerx = 100;
	int playery = 200;
	int playerw = 50;
	int playerh = 50;

	int platformx = 100;
	int platformy = 300;
	int platformw = 200;
	int platformh = 20;

	void Jump();
	void Collision();
};


