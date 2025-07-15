#pragma once
#include "IntegrationLibrary.h"

class TitleScreen {
public:
    TitleScreen(const std::string& backgroundTexturePath);
    void run(sf::RenderWindow& window);

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;   // 이 부분에서 기본 생성자 오류가 발생할 수 있습니다.

    sf::Font font;
    sf::Text titleText;            // 이 부분에서 기본 생성자 오류가 발생할 수 있습니다.
};