#include "Platform.h"

Platform::Platform() : platformSprit(platformTex)
{
	if (!platformTex.loadFromFile("PlatformAssets/Platform.png"))
	{
		cout << "에러 : 플랫폼 스프라이트를 찾을 수 없음" << endl;
		return;
	}
	platformRect = IntRect({ 0,0 }, { 440,50 });
	platformSprit.setTextureRect(platformRect);
	platformSprit.setOrigin({ 30.f,30.f });
	platformSprit.setPosition({ 400.f,300.f });
	SetPlatformPos();
}

void Platform::SetPlatformPos()
{
	platformPos.x = platformSprit.getPosition().x;
	platformPos.y = platformSprit.getPosition().y;
}



Pos Platform::GetPlatformPos()
{
	SetPlatformPos();
	return platformPos;
}


void Platform::Draw(RenderWindow& window)
{
	window.draw(platformSprit);
}
