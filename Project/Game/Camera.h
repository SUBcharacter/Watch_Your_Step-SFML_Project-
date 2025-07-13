#pragma once
#include "IntegrationLibrary.h"

class Camera
{
private:
	sf::View view;

	// 화면 경계 (플레이어가 여기 닿으면 카메라 이동)
	float C_top;
	float C_bottom;

	// 카메라 중심 위치 관리
	float C_viewWidth;
	float C_viewHeight ;


public:
	Camera(float width, float height); // 화면 너비와 높이 입력받아 초기화

	void C_UpdateView(const sf::Vector2f& playerPositon); // 플레이어 위치에 따라 카메라 업뎃

	sf::View C_GetView() const; // 뷰 반환



};

