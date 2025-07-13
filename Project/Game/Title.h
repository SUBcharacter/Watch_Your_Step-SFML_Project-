#pragma once
#include "IGameState.h"
#include <optional>
#include "Game_Manager.h"

class Title : public IgameState
{
private:
    sf::Texture m_backgroundTexture; // 배경 텍스처
    std::optional<sf::Sprite> m_backgroundSprite;                 // 배경 스프라이트
    sf::Font m_font;                 // 폰트
    std::optional<sf::Text> m_titleText;            // 제목 텍스트
    std::optional<sf::Text> m_pressEnterText;       // "Press Enter" 텍스트

public:

    Title();
    virtual ~Title() override;
    void onEnter(Game_Manager& game) override;
    void handleInput(Game_Manager& game, const sf::Event& event) override;
    void update(Game_Manager& game, float deltaTime) override;
    void draw(Game_Manager& game, sf::RenderWindow& window) override;
    void onExit(Game_Manager& game) override;


};


