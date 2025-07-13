#include "Platform.h"

Platform::Platform(int left, int top, int width, int height) : sprite(texture)
{
	if (!texture.loadFromFile("Assets/platform.png"))
	{
		cerr << "에러 : 텍스쳐 파일 없음" << endl;
		return;
	}
	IntRect rectI = { {left,top},{width,height} };
	FloatRect rectF =
	{ {static_cast<Vector2f>(rectI.position)},
	  { static_cast<Vector2f>(rectI.size)}
	};
	sprite.setTextureRect(rectI);
	sprite.setOrigin({ width/2, height/2 });
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
