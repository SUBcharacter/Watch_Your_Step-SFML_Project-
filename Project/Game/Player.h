#pragma once
#include "IntegrationLibrary.h"

class Player
{
private:
	FloatRect player;
	Texture playerTexture;
	Sprite playerSprite;

	const float GRAVITY = 900.f;
	float groundY = 500.f;
	
	FloatRect hitBox;
	FloatRect senseBox;
  
public:
	Player();
	float velocityY = 0.f;
	bool IsOnGround = false;


	void SetPlayerPos(float x,float y);

	void Updatehitbox();
	void UpdatesenseBox();

	FloatRect& GetSenseBox();
	vector<pair<int, int>> GetnearGridcells();
	Vector2f GetPlayerPos();
	FloatRect& GetHitBox();
	
	void Draw(RenderWindow& window);
	void Move(float deltaTime);
};

