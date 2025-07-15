// TitleScreen.hpp

#pragma once

#include "IntegrationLibrary.h"

// GameState 열거형 (TitleScreen이 다음 상태를 외부에 알려줄 때 필요)
enum class GameState {
    MainMenu,   // 타이틀 화면
    Playing,    // 게임 플레이 중
    Options,    // 옵션 화면
    Exiting     // 게임 종료
};

class TitleScreen
{
public:
    TitleScreen(int left, int top, int width, int height);
    GameState run(sf::RenderWindow& window);

private:
    sf::Texture backTexture;
    sf::Sprite backSprite;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    sf::Font mFont;
    sf::Text startButton;
    sf::Text exitButton;

    int m_left;
    int m_top;
    int m_width;
    int m_height;

    int m_selectedButtonIndex;
    std::vector<sf::Text*> m_buttons;

    bool m_finished = false;
    GameState m_nextState = GameState::MainMenu;

    void loadAssets();
    void handleEvent(const sf::Event& event);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void updateButtonSelection();
    void activateSelectedButton();
    bool isButtonClicked(const sf::Text& button, const sf::Vector2f& mousePos);
};