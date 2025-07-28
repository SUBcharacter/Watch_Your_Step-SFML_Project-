/*

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
    TitleScreen( RenderWindow& window, const std::string& backgroundTexturePath);
    ~TitleScreen();

    void run();

private:
     RenderWindow& m_window;

     View m_titleView;
     View m_gameplayView;

    GameState m_currentState;

     Texture b_texture;
     Sprite b_Sprite;

     Font m_font;  
    bool m_fontLoaded = false;
     Text m_titleText;

    std::vector<std::string> m_optionStrings;
    std::vector< Text> m_optionTexts;
    int m_highlightedOptionIndex;

    const  Color m_defaultOptionColor =  Color::White;
    const  Color m_highlightOptionColor =  Color::Yellow;

     Clock m_keyPressClock;
     Time m_keyPressDelay;

     Texture m_indicatorTexture; // 지시자 스프라이트의 텍스처
     Sprite m_indicatorSprite;   // 지시자 스프라이트

    void initViews();
    void setupTitleElements(const std::string& backgroundTexturePath);
    void setupOptions();
    void initGameplayElements();

    void update(float deltaTime);
    void render();

    void handleTitleStateEvents(const  Event& event);
    void handleGameplayStateEvents(const  Event& event);

    void updateTitleState(float deltaTime);
    void updateGameplayState(float deltaTime);
    void handleEvents();

    void renderTitleState();
    void renderGameplayState();

    TitleButton getButtonClicked(const  Vector2f& mousePos);
};
*/