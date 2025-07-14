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

	
public:
	
	Platform();
	void SetPlatformPos();
	Pos GetPlatformPos();
	void Draw(RenderWindow& window);
};

