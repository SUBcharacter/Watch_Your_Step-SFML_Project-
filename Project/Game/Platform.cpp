#include "Platform.h"


Platform::Platform(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height)
	: sprite(texture), type(type)
{
	
	if (!texture.loadFromFile(texturePath))
	{
		cerr << "에러 : 텍스쳐 파일 없음" << endl;
		return;
	}
	IntRect rectI = { {left,top},{width,height} };
	FloatRect rectF =
	{ 
	  {static_cast<Vector2f>(rectI.position)},
	  { static_cast<Vector2f>(rectI.size)}
	};
	sprite.setTextureRect(rectI);
	sprite.setOrigin({ rectF.size.x / 2.f, rectF.size.y / 2.f });
	hitBoxSize = static_cast<Vector2f>(rectI.size);
	SetPosition(pos);
}

PlatformType Platform::GetType()
{
	return type;
}

FloatRect Platform::GetHitBox()
{
	return hitBox;
}

void Platform::UpdateHitBox()
{
	Vector2f worldPos = sprite.getPosition();
	Vector2f origin = sprite.getOrigin();
	Vector2f criteria = worldPos - origin;

	hitBox = { criteria, hitBoxSize };

}

void Platform::SetPosition(Vector2f pos)
{
	sprite.setPosition(pos);
	UpdateHitBox();
}

Vector2f Platform::GetPosition()
{
	return sprite.getPosition();
}

void Platform::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Platform::OnCollide(Player& p, CollideDir dir)
{
	FloatRect playerHB = p.GetHitBox();
	FloatRect platformHB = this->GetHitBox();

	switch (dir)
	{
	case TOP:
		p.SetPlayerPos(p.GetPlayerPos().x, platformHB.position.y - (playerHB.size.y / 2));
		p.IsOnGround = true;
		break;
	case LEFT_SIDE:
		p.SetPlayerPos(platformHB.position.x - (playerHB.size.x / 2),p.GetPlayerPos().y);
		break;
	case RIGHT_SIDE:
		p.SetPlayerPos(platformHB.position.x + (playerHB.size.x / 2), p.GetPlayerPos().y);
		break;
	case UNDER:
		p.SetPlayerPos(p.GetPlayerPos().x, platformHB.position.y + (playerHB.size.y / 2));
		break;
	}
}

JumpPlatform::JumpPlatform(const string& texturePath, Vector2f pos, int left, int top, int width, int height, float jumpForce)
	: Platform(texturePath, type, pos, left, top, width, height), jumpForce(jumpForce)
{
	isActive = true;
	ignoreDuration = 1.0f;
	ignoreTimer = 0.0f;
}

void JumpPlatform::Update(float deltaTime)
{
	if (!isActive)
	{
		ignoreTimer += deltaTime;
		if (ignoreTimer >= ignoreDuration)
		{
			isActive = true;
			ignoreTimer = 0.0f;	
		}
	}
}

void JumpPlatform::OnCollide(Player& p, CollideDir dir)
{
	if (!isActive)
		return;

	p.velocityY -= jumpForce;
	isActive = false;
	ignoreTimer = 0.f;
}

MovingPlatform::MovingPlatform(const string& texturePath, Vector2f pos, int left, int top, int width, int height, float mr, float speed, int dir, Player& player)
	: Platform(texturePath, type, pos, left, top, width, height), moveRange(mr), speed(speed), direction(dir)
{
	startPos = pos;
	prevPos = pos;
}

void MovingPlatform::Update(float deltaTime)
{
	prevPos = GetPosition();

	float movement = speed * deltaTime * direction;
	Vector2f newPos = GetPosition();
	newPos.x += movement;

	float leftBound = startPos.x - moveRange;
	float rightBound = startPos.x + moveRange;

	if (newPos.x < leftBound)
	{
		newPos.x = leftBound;
		direction = 1;
	}
	else if (newPos.x > rightBound)
	{
		newPos.x = rightBound;
		direction = -1;
	}

	SetPosition(newPos);
}

void MovingPlatform::OnCollide(Player& p, CollideDir dir)
{
	FloatRect playerHB = p.GetHitBox();
	FloatRect platformHB = this->GetHitBox();

	switch (dir)
	{
	case TOP:
		Vector2f delta = GetPosition() - prevPos;
		Vector2f newPlayerPos = p.GetPlayerPos();
		newPlayerPos.x += delta.x;
		p.SetPlayerPos(newPlayerPos.x, platformHB.position.y - (playerHB.size.y / 2));
		break;
	case LEFT_SIDE:
		p.SetPlayerPos(platformHB.position.x - (playerHB.size.x / 2), p.GetPlayerPos().y);
		break;
	case RIGHT_SIDE:
		p.SetPlayerPos(platformHB.position.x + (playerHB.size.x / 2), p.GetPlayerPos().y);
		break;
	case UNDER:
		p.SetPlayerPos(p.GetPlayerPos().x, platformHB.position.y + (playerHB.size.y / 2));
		break;
	}
}
