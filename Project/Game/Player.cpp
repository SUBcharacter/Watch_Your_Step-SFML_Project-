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
	playerSprite.setPosition({ 300.f,500.f });
	SetPlayerPos();

	
	hitbox.setSize(sf::Vector2f(30, 30));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1.f);
	Updatehitbox();
	UpdatesenseBox();

}

void Player::SetPlayerPos()
{
	playerPos.x = playerSprite.getPosition().x;
	playerPos.y = playerSprite.getPosition().y;
}

Pos Player::GetPlayerPos()
{
	SetPlayerPos();
	return playerPos;
}

void Player::Updatehitbox()
{
	Vector2f spritepos = playerSprite.getPosition();
	Vector2f hitboxsize = hitbox.getSize();
	Vector2f hitboxPos = spritepos - (hitboxsize / 2.f);
	hitbox.setPosition(hitboxPos);
}

void Player::UpdatesenseBox()
{
	Vector2f spritespos = playerSprite.getPosition();
	Vector2f offset(-48.f, -40.f); 
	senseBox.setPosition(spritespos + offset);
}

void Player::Draw(RenderWindow& window)
{
	window.draw(playerSprite);
	window.draw(hitbox);
}

sf::FloatRect Player::GethitboxBounds()
{
	return hitbox.getGlobalBounds();
}

Player::HitboxRect& Player::Gethitbox()
{
	Vector2f pos = hitbox.getPosition();
	Vector2f size = hitbox.getSize();

	static HitboxRect r;

	r.Left = pos.x;
	r.Right = pos.x + size.x;
	r.Top = pos.y;
	r.Bottom = pos.y + size.y;

	return r;
}
RectangleShape& Player::GetSenseBox()
{
	return senseBox;
}


vector<pair<int, int>> Player::GetnearGridcells()
{
	vector<pair<int, int>> nearplatform;

	FloatRect bounds = senseBox.getGlobalBounds();

	float left = bounds.position.x;
	float top = bounds.position.y;
	float right = bounds.position.x + bounds.size.x;
	float bottom = bounds.position.y + bounds.size.y;

	float cellsize = 100.f;

	int gridleft = static_cast<int>(floor(left / cellsize));
	int gridright = static_cast<int>(floor(right / cellsize));
	int gridtop = static_cast<int>(floor(top / cellsize));
	int gridbottom = static_cast<int>(floor(bottom / cellsize));

	for (int y = gridtop; y <= gridbottom ; y++)
	{
		for (int x = gridleft; x <= gridright; x++)
		{
			nearplatform.emplace_back(x, y);
		}
	}
	return nearplatform;
}
void Player::Move(float deltaTime)
{
#pragma region 점프(임시)

	bool jumpKey = Keyboard::isKeyPressed(Keyboard::Scan::W);

	if (jumpKey && !jumpKeyPressedLastFrame)
	{
		if (IsOnGround)
		{
			velocityY = -300.f;
			Doublejump = false;
			IsOnGround = false;
		}
		else if (!Doublejump)
		{
			velocityY = -300.f;
			Doublejump = true;
		}
	}
	jumpKeyPressedLastFrame = jumpKey;
	if (!IsOnGround)
	{
		velocityY += GRAVITY * deltaTime;
		playerSprite.move({ 0.0f, velocityY * deltaTime });
	}
	if (playerSprite.getPosition().y >= groundY)
	{
		playerSprite.setPosition({ playerSprite.getPosition().x,groundY });
		velocityY = 0.f;
		IsOnGround = true;
	}

#pragma endregion


	if (Keyboard::isKeyPressed(Keyboard::Scan::A) && playerSprite.getPosition().x > 0)
	{
		playerSprite.move({ -200.0f * deltaTime ,0.0f });
		playerSprite.setTextureRect(playerRect);
		playerSprite.setScale({ -1.0f, 1.0f });
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::D) && playerSprite.getPosition().x < 600)
	{
		playerSprite.move({ 200.0f * deltaTime ,0.0f });
		playerSprite.setTextureRect(playerRect);
		playerSprite.setScale({ 1.0f, 1.0f });

	}

	Updatehitbox();

}


