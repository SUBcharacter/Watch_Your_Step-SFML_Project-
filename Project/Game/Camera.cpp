#include "Camera.h"

Camera::Camera(float width, float height)
	: view(sf::Vector2f(width / 2.f, height / 2.f), sf::Vector2f(width, height)),
	C_viewWidth(width), C_viewHeight(height)
{
	// ���Ʒ� ��� ���� (��������)
	C_top = 350.f;
	C_bottom = 350.f;
}

void Camera::C_UpdateView(const sf::Vector2f& playerPosition)
{
	// ���� view�� �� ���� �� �Ʒ� ����
	float topOfView = view.getCenter().y - C_viewHeight / 2.f;
	float bottomOfView = view.getCenter().y + C_viewHeight / 2.f;

	if (playerPosition.y < topOfView + C_top) // �÷��̾ ���� �ö󰡸�
	{
		float offset = (topOfView + C_top) - playerPosition.y;
		view.move(sf::Vector2f(0.f, -offset)); // ī�޶� ���� �̵�
	}

	else if (playerPosition.y > bottomOfView - C_bottom) // �÷��̾ �Ʒ��� ��������
	{
		float offset = playerPosition.y - (bottomOfView - C_bottom);
		view.move(sf::Vector2f(0.f, offset)); // ī�޶� �Ʒ��� �̵�
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
