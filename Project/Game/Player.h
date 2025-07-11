#pragma once
#include "IntegrationLibrary.h"

class Player
{
private:
	struct Pos
	{
		float x;
		float y;
	};
	IntRect playerRect;
	Texture playerTexture;
	Sprite playerSprite;

	float velocityY = 0.f;
	const float GRAVITY = 0.5f;
	float groundY = 500.f;
	bool hasDoubleJumped = false;
	bool isOnGround = false;
	bool jumpKeyPressedLastFrame = false;
	//Physics& playerPhysics;  // 물리 클래스

public:
	Player();
	
	void Draw(RenderWindow& window);
	void Move();
};

