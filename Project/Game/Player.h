#pragma once
#include "IntegrationLibrary.h"

class Player
{
private:
	Texture texture;
	Sprite sprite;

	SoundBuffer jumpBuffer;
	SoundBuffer stepBuffer;

	Sound* jumpSound;
	Sound* stepSound;

	const float GRAVITY = 900.f;
	float CrowdControlTimer = 0.f;

	Vector2f hitBoxSize;
	FloatRect hitBox;

	FloatRect senseBox;

	enum class PlayerState
	{
		Idle,
		R_Running,
		L_Running,
		Jumping
	};

	PlayerState currentState = PlayerState::Idle;

	const int frameWidth = 30;
	const int frameHeight = 40;

	bool animationIndex = 0;
	float animationTimer = 0.f;
	float animationIntervel = 0.15f; // 프레임 전환 간격. 수정가능.

	Vector2f senceBoxSize;
	FloatRect senceBox;

  
public:
	Player(const string& texturePath, Vector2f pos,int left, int top, int width, int height);
	float velocityY = 0.f;
	bool IsOnGround = false;
	bool CrowdControl = false;
	
	void Update(float deltaTime);

	void SetPlayerPos(Vector2f pos);

	void Updatehitbox();
	void UpdatesenseBox();
	void CrowdControlUpdate(float deltaTime);
	void SetCrowdControlTimer(float time);
	
	void UpdateAnimation(float deltaTime);

	void PlayJumpSound();
	void PlayStepSound();

	FloatRect& GetSenseBox();
	vector<pair<int, int>> GetnearGridcells();
	Vector2f GetPlayerPos();
	FloatRect& GetHitBox();
	
	void Draw(RenderWindow& window);
	void Move(float deltaTime);
	~Player();
};

