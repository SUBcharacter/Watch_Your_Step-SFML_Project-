#pragma once
#include "IntegrationLibrary.h"
#include "Player.h"

class Platform
{
protected:
	PlatformType type;
	Texture texture;
	Sprite sprite;
	Vector2f hitBoxSize;
	FloatRect hitBox;

public:
	vector<pair<int, int>> registeredCells;

	Platform(const string& texturePath,PlatformType type, Vector2f pos, int left, int top, int width, int height);
	virtual ~Platform() = default;

	virtual PlatformType GetType();

	virtual FloatRect GetHitBox();

	virtual void UpdateHitBox();

	virtual void SetPosition(Vector2f pos);

	virtual Vector2f GetPosition();

	virtual void Draw(RenderWindow& window);

	virtual void Update(float deltaTime) {}

	virtual void OnCollide(Player& p, CollideDir dir);

};

class JumpPlatform : public Platform
{
private:
	bool isActive;
	float ignoreTimer;
	float ignoreDuration; 
	float jumpForce;

public:
	JumpPlatform(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height, float jumpForce);

	void Update(float deltaTime) override;

	void OnCollide(Player& p, CollideDir dir) override;

};

class MovingPlatform : public Platform
{
private:
	float speed;
	float moveRange;
	int direction;
	Vector2f startPos;
	Vector2f prevPos;

public:
	MovingPlatform(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height,
		float mr, float speed, int dir);


	void Update(float deltaTime) override;

	void OnCollide(Player& p, CollideDir dir) override;
};

