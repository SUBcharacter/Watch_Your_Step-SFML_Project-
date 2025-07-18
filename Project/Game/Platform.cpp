#include "Platform.h"


Platform::Platform(const string& texturePath, int left, int top, int width, int height) : sprite(texture)
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

void Platform::SetPosition(float x, float y)
{
	sprite.setPosition(Vector2f(x, y));
	UpdateHitBox();
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
