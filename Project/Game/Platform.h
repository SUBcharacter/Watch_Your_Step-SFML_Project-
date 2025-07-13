#pragma once
#include "IntegrationLibrary.h"

class Platform
{
private:
	Texture texture;
	Sprite sprite;
	Vector2f hitBoxSize;
	FloatRect hitBox;

public:
	Platform(int left, int top, int width, int height);

	FloatRect GetHitBox();

	void UpdateHitBox();
	void SetPosition(float x, float y);
	void Draw(RenderWindow& window);

};

