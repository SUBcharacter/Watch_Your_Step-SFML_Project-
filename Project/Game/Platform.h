#pragma once
#include "IntegrationLibrary.h"
#include "Player.h"
#include <vector>
class Platform
{
private:
	Pos platformPos;
	IntRect platformRect;
	Texture platformTex;
	Sprite platformSprit;

	bool Collied = false;
public:
	
	Platform();
	void SetPlatformPos();
	sf::FloatRect getBounds()
	{
		return platformSprit.getGlobalBounds();
	}
	Pos GetPlatformPos();
	void update(Player& player,vector<Platform>& platform);
	void Draw(RenderWindow& window);
};

