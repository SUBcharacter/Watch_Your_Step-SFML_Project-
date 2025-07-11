#pragma once
#include "IntegrationLibrary.h"

class Physics
{
private:
	int h = 0;
	bool fall = false;
	float t = 0.0f;
	const float G = 9.81f;
	const float Vo = 11.f;

	float velocityY = 0.0f;
	float gravity = 0.5f;
	bool isOnGround = false;
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

