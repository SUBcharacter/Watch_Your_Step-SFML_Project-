#pragma once
#include "IntegrationLibrary.h"

class Player
{
private:
	
	Pos playerPos;
	IntRect playerRect;
	Texture playerTexture;
	Sprite playerSprite;

	float velocityY = 0.f;
	const float GRAVITY = 900.f;
	float groundY = 500.f;
	//Physics& playerPhysics;  // 물리 클래스

public:
	Player();
	
	void SetPlayerPos();
	Pos GetPlayerPos();

	void Draw(RenderWindow& window);
	void Move();
	void Move(float deltaTime);
};

