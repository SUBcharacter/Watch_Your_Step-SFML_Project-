#include "Camera.h"

Camera::Camera(float width, float height)
	: view(sf::Vector2f(width / 2.f, height / 2.f), sf::Vector2f(width, height)),
	C_viewWidth(width), C_viewHeight(height)
{
	// 위아래 경계 설정 (조절가능)
	C_top = 200.f;
	C_bottom = 200.f;
}

void Camera::C_UpdateView(const sf::Vector2f& playerPosition)
{
	// 현재 view의 맨 위와 맨 아래 선언
	float topOfView = view.getCenter().y - C_viewHeight / 2.f;
	float bottomOfView = view.getCenter().y + C_viewHeight / 2.f;

	if (playerPosition.y < topOfView + C_top) // 플레이어가 위로 올라가면
	{
		float offset = (topOfView + C_top) - playerPosition.y;
		view.move(sf::Vector2f(0.f, -offset)); // 카메라도 위로 이동
	}

	else if (playerPosition.y > bottomOfView - C_bottom) // 플레이어가 아래로 내려가면
	{
		float offset = playerPosition.y - (bottomOfView - C_bottom);
		view.move(sf::Vector2f(0.f, offset)); // 카메라도 아래로 이동
	}
}

void Camera::C_StartGame(const sf::Vector2f& playerPositon)
{
	view.setCenter(playerPositon);
}

sf::View Camera::C_GetView() const
{
	return view;
}
