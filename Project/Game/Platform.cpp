#include "Platform.h"

Platform::Platform() : platformSprite(platformTex)
{
	if (!platformTex.loadFromFile("Assets/platform.png"))
	{
		cerr << "에러 : 텍스쳐 파일 없음" << endl;
		return;
	}
	platformSprite.setTexture(platformTex);
	FloatRect bounds = platformSprite.getGlobalBounds();
	platformSprite.setOrigin(bounds.width/2.f)
}
