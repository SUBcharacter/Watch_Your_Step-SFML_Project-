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

	PlatformType GetType();

	FloatRect GetHitBox();

	void UpdateHitBox();

	void SetPosition(Vector2f pos);

	Vector2f GetPosition();

	void Draw(RenderWindow& window);

	virtual void Update(float deltaTime) {}

	virtual void OnCollide(Player& p, CollideDir dir);

};

class JumpPlatform : public Platform
{
private:
	bool isActive;
	float ignoreTimer; // 무시 타이머
	float ignoreDuration; // 무시 지속 시간(초)
	float jumpForce;

public:
	JumpPlatform(const string& texturePath, Vector2f pos, int left, int top, int width, int height, float jumpForce);

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
	MovingPlatform(const string& texturePath, Vector2f pos, int left, int top, int width, int height,
		float mr, float speed, int dir, Player& player);

	void Update(float deltaTime) override;

	void OnCollide(Player& p, CollideDir dir) override;
};

