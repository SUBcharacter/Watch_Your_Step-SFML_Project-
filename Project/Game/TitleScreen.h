// TitleScreen.h
#pragma once

#include "IntegrationLibrary.h" // SFML 3.0 관련 헤더 포함 가정

enum GameState
{
    TITLE,
    GAMEPLAY,
};

enum class TitleButton {
    StartGame,
    ExitGame,
    None
};

class TitleScreen {
public:
    TitleScreen(sf::RenderWindow& window, const std::string& backgroundTexturePath);
    ~TitleScreen();

    void run();

private:
    sf::RenderWindow& m_window;

    sf::View m_titleView;
    sf::View m_gameplayView;

    GameState m_currentState;

    sf::Texture m_backgroundTexture;
    sf::Sprite* m_backgroundSprite;

    sf::Font m_font;  
    bool m_fontLoaded = false;
    sf::Text* m_titleText;

    std::vector<std::string> m_optionStrings;
    std::vector<sf::Text> m_optionTexts;
    int m_highlightedOptionIndex;

    const sf::Color m_defaultOptionColor = sf::Color::White;
    const sf::Color m_highlightOptionColor = sf::Color::Yellow;

    sf::Clock m_keyPressClock;
    sf::Time m_keyPressDelay;

    sf::Texture m_indicatorTexture; // 지시자 스프라이트의 텍스처
    sf::Sprite m_indicatorSprite;   // 지시자 스프라이트

    void initViews();
    void setupTitleElements(const std::string& backgroundTexturePath);
    void setupOptions();
    void initGameplayElements();

    void update(float deltaTime);
    void render();

    void handleTitleStateEvents(const sf::Event& event);
    void handleGameplayStateEvents(const sf::Event& event);

    void updateTitleState(float deltaTime);
    void updateGameplayState(float deltaTime);
    void handleEvents();

    void renderTitleState();
    void renderGameplayState();

    TitleButton getButtonClicked(const sf::Vector2f& mousePos);
};