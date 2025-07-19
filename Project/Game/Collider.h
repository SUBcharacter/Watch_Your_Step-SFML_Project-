#pragma once
#include "IntegrationLibrary.h"
#include "Platform.h"
#include "Player.h"



class Collider
{
private:
	Player& player;
	
public:
	Collider(Player& player) : player(player) {}

	bool isColliding(const FloatRect& player, const FloatRect& platform);
	CollideDir CollidingDirection(const FloatRect& player, const FloatRect& platform);
	void Collider2D(vector<Platform*> nearPlatform);

};

