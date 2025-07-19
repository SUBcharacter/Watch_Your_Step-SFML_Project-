#pragma once
#include "IntegrationLibrary.h"


/*

<Camera 클래스 설명>

- 플레이어가 상단/하단 경계(생성자 내에서 조절 가능)에 닿으면 카메라가 위아래로 이동함.

- 게임 시작 시 플레이어 위치를 기준으로 카메라가 초기화됨.
  따라서, 첫 시작 시 플레이어를 화면 중앙에 위치시키는 것이 중요함.
  (필요시 개선 가능하니 말씀해주세요.)

<Camera 클래스 사용 방법>

1. 카메라 생성
   Camera camera(너비, 높이);
   우리 게임 해상도는 600 * 800이므로
   Camera camera(600, 800); 으로 생성하면 됩니다.

2. 타이틀 화면 뷰 설정
   타이틀 영역이 (0,0) ~ (600,800)이라면,
   camera.C_StartGame(sf::Vector2f(300.f, 400.f)); ->  타이틀 화면 중앙 좌표로 카메라 초기 위치 설정

   게임 플레이 화면을 처음 비출 때,
   camera.C_StartGame(playerPosition); -> 플레이어 위치로 카메라 초기 위치 설정

3. 매 프레임마다 플레이어 위치에 맞춰 카메라 업데이트
   camera.C_UpdateView(playerPosition);

4. 매 프레임 그리기 전에 호출하여 뷰 적용
   window.setView(camera.C_GetView());

*/


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

	void C_StartGame(const sf::Vector2f& playerPositon); // 게임 시작할 때 플레이어를 비추게 함

	sf::View C_GetView() const; // 뷰 반환



};

