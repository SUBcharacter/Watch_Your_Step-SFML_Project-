#pragma once
#include <SFML/Graphics.hpp>
#include "IntegrationLibrary.h" // 이 헤더가 필요한 경우 유지합니다.

class TitleScreen {
public:
    // 생성자: 배경 이미지 파일 경로를 받아 초기화합니다.
    TitleScreen(const std::string& backgroundTexturePath);

    // run() 함수: 전달받은 윈도우에 타이틀 화면을 표시하고 이벤트를 처리합니다.
    // 윈도우가 닫히거나 특정 키가 눌리면 함수를 종료합니다.
    void run(sf::RenderWindow& window); // sf::RenderWindow를 참조로 받도록 변경

private:
    sf::Texture backgroundTexture; // 배경 이미지를 담을 텍스처
    sf::Sprite backgroundSprite;   // 텍스처를 사용하여 화면에 그릴 스프라이트

    sf::Font font;                 // 타이틀 텍스트에 사용할 폰트
    sf::Text titleText;            // 타이틀 문자열을 표시할 sf::Text 객체
};