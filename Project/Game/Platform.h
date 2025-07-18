#pragma once
#include "IntegrationLibrary.h"
#include "Player.h"

class Platform
{
protected:
	Texture texture;
	Sprite sprite;
	Vector2f hitBoxSize;
	FloatRect hitBox;

public:
	Platform(const string& texturePath, int left, int top, int width, int height);
	virtual ~Platform() = default;

	FloatRect GetHitBox();

	void UpdateHitBox();

	void SetPosition(float x, float y);

	void Draw(RenderWindow& window);

	virtual void Update() {}

	virtual void OnCollide(Player& p, CollideDir dir);

};

class BouncePlatform : public Platform
{

};

class MovingPlatform : public Platform
{

};

