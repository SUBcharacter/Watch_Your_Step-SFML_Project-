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
	hitBoxSize = rectF.size;
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
		p.SetPlayerPos({ p.GetPlayerPos().x, platformHB.position.y - (playerHB.size.y / 2) });
		p.IsOnGround = true;
		break;
	default:
		p.IsOnGround = false;
	}
}

JumpPlatform::JumpPlatform(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height, float jumpForce)
	: Platform(texturePath, type, pos, left, top, width, height), jumpForce(jumpForce)
{
	isActive = true;
	ignoreDuration = 0.01f;
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

	if (jumpForce >= 3000.f)
	{
		p.CrowdControl = true;
		p.SetCrowdControlTimer(2.f);
	}
	else if (jumpForce >= 2400.f)
	{
		p.CrowdControl = true;
		p.SetCrowdControlTimer(1.75f);
	}
	else if (jumpForce >= 1800.f)
	{
		p.CrowdControl = true;
		p.SetCrowdControlTimer(1.5f);
	}
	else if (jumpForce >= 1200.f)
	{
		p.CrowdControl = true;
		p.SetCrowdControlTimer(1.f);
	}
	else
	{
		p.CrowdControl = true;
		p.SetCrowdControlTimer(0.5f);
	}
	
	p.velocityY -= jumpForce + p.velocityY;
	isActive = false;
	ignoreTimer = 0.f;
}

MovingPlatform::MovingPlatform(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height, float mr, float speed, int dir)
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

	float leftBound = startPos.x - moveRange/2.f;
	float rightBound = startPos.x + moveRange/2.f;

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

	Vector2f delta = GetPosition() - prevPos;
	Vector2f newPlayerPos = p.GetPlayerPos();
	switch (dir)
	{
	case TOP:
		newPlayerPos.x += delta.x * 2;
		p.SetPlayerPos({ newPlayerPos.x, platformHB.position.y - (playerHB.size.y / 2) });
		p.IsOnGround = true;
		break;
	default:
		p.IsOnGround = false;
	}
}
