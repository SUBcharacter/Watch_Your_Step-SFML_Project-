#pragma once
#include "IntegrationLibrary.h"

class Player
{
private:

	Texture playerTexture;
	Sprite playerSprite;

	float velocityY = 0.f;
	const float GRAVITY = 900.f;
	float groundY = 500.f;
	bool IsOnGround = false;
	bool jumpKeyPressedLastFrame = false;

	 RectangleShape hitbox;
	 RectangleShape senseBox;

public:
	Player();
	
	void SetPlayerPos(float x,float y);
	Pos GetPlayerPos();

	void Updatehitbox();
	void UpdatesenseBox();

	RectangleShape& GetSenseBox();
	vector<pair<int, int>> GetnearGridcells();

	void Draw(RenderWindow& window);
	void Move(float deltaTime);
};

