#include "Player.h"

Player::Player() : playerSprite(playerTexture)
{
	if (!playerTexture.loadFromFile("Assets/player.png"))
	{
		cerr << "에러 : player 스프라이트 찾을 수 없음." << endl;
		return;
	}
	playerRect = IntRect({ 0,0 }, { 50,50 });
	playerSprite.setTextureRect(playerRect);
	playerSprite.setOrigin({ 25.f,25.f });
	playerSprite.setPosition({ 300,400 });
}

void Player::Draw(RenderWindow& window)
{
	window.draw(playerSprite);
}

void Player::Move()
{
#pragma region 점프(임시)

	bool jumpKeyNowPressed = Keyboard::isKeyPressed(Keyboard::Scan::W);

	if (jumpKeyNowPressed && !jumpKeyPressedLastFrame)
	{
		if (isOnGround)
		{
			velocityY = -10.f;
			isOnGround = false;
		}
		else if (!hasDoubleJumped);
		{
			velocityY = -10.f;
			hasDoubleJumped = true;
		}
	}

	jumpKeyPressedLastFrame = jumpKeyNowPressed;
	if (!isOnGround)
	{
		velocityY += GRAVITY;
		playerSprite.move({ 0.0f, velocityY });
	}

	if (playerSprite.getPosition().y >= groundY)
	{
		playerSprite.setPosition({ playerSprite.getPosition().x,groundY });
		velocityY = 0.f;
		isOnGround = true;
		hasDoubleJumped = false;
	}

#pragma endregion


	if (Keyboard::isKeyPressed(Keyboard::Scan::A) && playerSprite.getPosition().x > 0)
	{
		playerSprite.move({ -2.0f,0.0f });
		playerSprite.setTextureRect(playerRect);
		playerSprite.setScale({ -1.0f, 1.0f });
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::D) && playerSprite.getPosition().x < 600)
	{
		playerSprite.move({ 2.0f,0.0f });
		playerSprite.setTextureRect(playerRect);
		playerSprite.setScale({ 1.0f, 1.0f });
	}
}


