#pragma once
#include "IntegrationLibrary.h"

class Player
{
private:

	Texture playerTexture;
	Sprite playerSprite;

	const float GRAVITY = 900.f;
	float groundY = 500.f;
	
	FloatRect hitBox;
	FloatRect senseBox;

	 RectangleShape hitbox;
	 RectangleShape senseBox;

public:
	Player();
	
	bool IsOnGround = false;
	float velocityY = 0.f;

	void SetPlayerPos(float x,float y);

	void Updatehitbox();
	void UpdatesenseBox();

	RectangleShape& GetSenseBox();
	vector<pair<int, int>> GetnearGridcells();

	void Draw(RenderWindow& window);
	void Move(float deltaTime);
};

