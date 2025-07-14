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
	bool IsOnGround = false;
	bool jumpKeyPressedLastFrame = false;
	bool Doublejump = false;


	//Physics& playerPhysics;  // 물리 클래스

	RectangleShape hitbox;
	RectangleShape senseBox;

	struct HitboxRect {
		float Left, Top, Bottom, Right;

		bool Intersect(HitboxRect& other) {
			return !(Right < other.Left || Left > other.Right || Bottom < other.Top || Top > other.Bottom);
		}
	};

public:
	Player();
	
	void SetPlayerPos();
	Pos GetPlayerPos();
	void Updatehitbox();
	HitboxRect& Gethitbox();
	void UpdatesenseBox();
	sf::FloatRect GethitboxBounds();
	RectangleShape& GetSenseBox();

	vector<pair<int, int>> GetnearGridcells();
	void Draw(RenderWindow& window);
	void Move(float deltaTime);
};

