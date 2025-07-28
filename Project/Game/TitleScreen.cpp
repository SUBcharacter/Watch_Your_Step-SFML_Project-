// TitleScreen.cpp
#include "TitleScreen.h"
#include <iostream>
/*
TitleScreen::TitleScreen(sf::RenderWindow& window, const std::string& backgroundTexturePath)
    : m_window(window),
    m_currentState(TITLE),
    b_Sprite(b_texture),
    m_titleText(nullptr),
    m_fontLoaded(false),
    m_highlightedOptionIndex(-1),
    m_keyPressClock(),
    m_keyPressDelay(sf::milliseconds(200))    
{  //<-여기서 '"sf::Sprite" 클래스의 기본 생성자가 없습니다.'오류때문에 결과물 확인 못했습니다.
    m_window.setFramerateLimit(60);

    if (!b_texture.loadFromFile(""))
    {
        cout << "에러 메세지" << endl;
    }
    b_Sprite.setTexture(b_texture);
    b_Sprite.setOrigin({600.0f, 400.0f});
    b_Sprite.setPosition({ 600.f, 400.0f });
    initViews();
    setupTitleElements(backgroundTexturePath);
    setupOptions();
}

TitleScreen::~TitleScreen() {
    
   m_optionTexts.clear();
}

void TitleScreen::initViews() {
    m_titleView.setCenter({ 1200.0f / 2.0f, 800.0f / 2.0f });
    m_titleView.setSize({ 1200.0f, 800.0f });

    m_gameplayView.setCenter({ 0.0f, 0.0f });
    m_gameplayView.setSize({ 1920.0f, 1080.0f });
}
void TitleScreen::setupTitleElements(const std::string& backgroundTexturePath) {
    // 1. 배경 텍스처 로드 및 스프라이트 생성
    if (!b_texture.loadFromFile("Assets/platform.png")) {
        std::cerr << "오류: 배경 텍스처를 로드할 수 없습니다: " << backgroundTexturePath << std::endl;
        b_Sprite = nullptr; 
       
    }
    else {
        if (b_Sprite) { delete b_Sprite; }
        b_Sprite = new sf::Sprite(b_texture);
        float scaleX = m_titleView.getSize().x / b_texture.getSize().x;
        float scaleY = m_titleView.getSize().y / b_texture.getSize().y;
        b_Sprite.setScale({ scaleX, scaleY });
    }

    // 2. 폰트 로드 및 타이틀 텍스트 생성
	if (!m_font.openFromFile("Assets/KoPubWorld Batang Medium.ttf" )) { // TODO: 실제 폰트 경로로 변경!
        std::cerr << "오류: 폰트를 로드할 수 없습니다. 폰트 경로를 확인하세요." << std::endl;
        m_titleText = nullptr; 
    }
    else {
        if (m_titleText) { delete m_titleText; }

        m_titleText = new sf::Text(m_font, sf::String("My Game Title"), 80);
        m_titleText->setFillColor(sf::Color::White); // 텍스트 색상 설정

            // 텍스트 원점 및 위치 설정 (기존 로직과 동일)
            sf::FloatRect textRect = m_titleText->getLocalBounds();
            m_titleText->setOrigin({
                textRect.position.x + textRect.size.x / 2.0f,
                textRect.position.y + textRect.size.y / 2.0f
                });
            m_titleText->setPosition({
                m_titleView.getCenter().x,
                m_titleView.getCenter().y / 2.0f
                });
    }
    if (!m_indicatorTexture.loadFromFile("Assets/player.png")) {
        std::cerr << "오류: 지시자 텍스처를 로드할 수 없습니다: Assets/player.png" << std::endl;
    }
    else {
        m_indicatorSprite.setTexture(m_indicatorTexture);
        sf::FloatRect indicatorRect = m_indicatorSprite.getLocalBounds();
        m_indicatorSprite.setOrigin({ indicatorRect.position.x + indicatorRect.size.x, indicatorRect.position.y + indicatorRect.size.y / 2.0f });
        m_indicatorSprite.setScale({ 0.5f, 0.5f }); 
    }
}
void TitleScreen::setupOptions() {
    m_optionTexts.clear();

    if (!m_fontLoaded) {
        std::cerr << "경고: 폰트가 로드되지 않아 옵션 텍스트를 생성할 수 없습니다." << std::endl;
        return;
    }

    m_optionStrings.push_back("Game Start");
    m_optionStrings.push_back("End");

    for (size_t i = 0; i < m_optionStrings.size(); ++i) {
        sf::Text optionText(m_font, sf::String(m_optionStrings[i]), 40);


        sf::FloatRect textRect = optionText.getLocalBounds();
        optionText.setOrigin({
            textRect.position.x + textRect.size.x / 2.0f,
            textRect.position.y + textRect.size.y / 2.0f
            });
        optionText.setPosition({
            m_titleView.getCenter().x,
            m_titleView.getCenter().y + 80.0f + static_cast<float>(i) * 80.0f
            });

        m_optionTexts.push_back(optionText);
    }
}
void TitleScreen::initGameplayElements() {
    std::cout << "게임 플레이 요소들이 초기화되었습니다!" << std::endl;
}

void TitleScreen::run() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        handleEvents();
        update(deltaTime);
        render();
    }
}
void TitleScreen::handleEvents() {
    while (true) {
        auto eventOpt = m_window.pollEvent(); 
        if (!eventOpt.has_value()) {
            break;
        }

        sf::Event& event = eventOpt.value(); // 이벤트 객체 참조

        if (event.is<sf::Event::Closed>()) {
            m_window.close();
        }

        event.visit([&](auto& ev) {
            using T = std::decay_t<decltype(ev)>;
            if constexpr (std::is_same_v<T, sf::Event::KeyPressed> ||
                std::is_same_v<T, sf::Event::MouseMoved> ||
                std::is_same_v<T, sf::Event::MouseButtonPressed>) {
                if (m_currentState == TITLE) {
                    handleTitleStateEvents(event);
                }
                else if (m_currentState == GAMEPLAY) {
                    handleGameplayStateEvents(event);
                }
            }
            });
    }
}


void TitleScreen::handleTitleStateEvents(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        if (m_keyPressClock.getElapsedTime() >= m_keyPressDelay) {
            if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Up) {
                    if (m_highlightedOptionIndex == -1) {
                        m_highlightedOptionIndex = m_optionTexts.size() - 1;
                    }
                    else {
                        m_highlightedOptionIndex = (m_highlightedOptionIndex - 1 + m_optionTexts.size()) % m_optionTexts.size();
                    }
                    m_keyPressClock.restart();
                }
                else if (keyEvent->code == sf::Keyboard::Key::Down) {
                    if (m_highlightedOptionIndex == -1) {
                        m_highlightedOptionIndex = 0;
                    }
                    else {
                        m_highlightedOptionIndex = (m_highlightedOptionIndex + 1) % m_optionTexts.size();
                    }
                    m_keyPressClock.restart();
                }
                else if (keyEvent->code == sf::Keyboard::Key::Enter) {
                // 엔터키 처리 부분은 나중에 구현 예정
                
                }

                else if (keyEvent->code == sf::Keyboard::Key::Escape) {
                  m_window.close();
                    return;
                }
            }
        }
    }
    else if (event.is<sf::Event::MouseMoved>()) {
        // 마우스 이동 시 하이라이트 변경 로직 (현재 마우스 위치를 사용하여 처리)
        sf::Vector2f mouseWorldPos = m_window.mapPixelToCoords(
            sf::Mouse::getPosition(m_window), m_titleView);

        int prevHighlightedIndex = m_highlightedOptionIndex;
        m_highlightedOptionIndex = -1; 

        for (size_t i = 0; i < m_optionTexts.size(); ++i) {
            if (m_optionTexts[i].getGlobalBounds().contains(mouseWorldPos)) {
                m_highlightedOptionIndex = static_cast<int>(i);
                break;
            }
        }
        // 하이라이트 변경 시 효과음 등을 재생할 수 있음 (prevHighlightedIndex와 비교)
    }
    else if (event.is<sf::Event::MouseButtonPressed>()) {
       if (auto mouseButtonEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonEvent->button == sf::Mouse::Button::Left) {
                sf::Vector2f mouseWorldPos = m_window.mapPixelToCoords(
                    sf::Mouse::getPosition(m_window), m_titleView);

                TitleButton clickedButton = getButtonClicked(mouseWorldPos);
                if (clickedButton == TitleButton::StartGame) {
                    m_currentState = GAMEPLAY;
                    initGameplayElements();
                    m_window.setView(m_gameplayView);
                    std::cout << "마우스로 새 게임 시작! 게임플레이 모드로 전환합니다." << std::endl;
                }
                else if (clickedButton == TitleButton::ExitGame) {
                    m_window.close(); // 게임 종료
                    std::cout << "마우스로 게임 종료." << std::endl;
                }
            }
        }
    }
}

void TitleScreen::handleGameplayStateEvents(const sf::Event& event) {
    // TODO: 게임 플레이 이벤트 처리
}



void TitleScreen::update(float deltaTime) {
    switch (m_currentState) {
    case TITLE:
        updateTitleState(deltaTime);
        break;
    case GAMEPLAY:
        updateGameplayState(deltaTime);
        break;
    }
}

void TitleScreen::updateTitleState(float deltaTime) {
    // 타이틀 화면은 정적이므로 별도 업데이트 없음
}

void TitleScreen::updateGameplayState(float deltaTime) {
    // TODO: 게임 플레이 로직 업데이트
}



void TitleScreen::render() {
    m_window.clear(sf::Color::Black);

    switch (m_currentState) {
    case TITLE:
        renderTitleState();
        break;
    case GAMEPLAY:
        renderGameplayState();
        break;
    }

    m_window.display();
}

void TitleScreen::renderTitleState() {
    m_window.setView(m_titleView);

    if (b_Sprite) {
        m_window.draw(*b_Sprite);
    }
    if (m_titleText) {
        m_window.draw(*m_titleText);
    }
    for (size_t i = 0; i < m_optionTexts.size(); ++i) {//메뉴
       m_optionTexts[i].setFillColor(
            (int)i == m_highlightedOptionIndex ? m_highlightOptionColor : m_defaultOptionColor
        );
        m_window.draw(m_optionTexts[i]);
    }

    if (m_highlightedOptionIndex >= 0 && m_highlightedOptionIndex < m_optionTexts.size() && m_indicatorTexture.getSize().x > 0) {
        sf::Text& highlightedText = m_optionTexts[m_highlightedOptionIndex];
        sf::FloatRect textBounds = highlightedText.getGlobalBounds();
            
        m_indicatorSprite.setPosition({
       textBounds.position.x - m_indicatorSprite.getGlobalBounds().size.x - 20.0f,
       textBounds.position.y + textBounds.size.y / 2.0f - m_indicatorSprite.getGlobalBounds().size.y / 2.0f
            });
        m_window.draw(m_indicatorSprite);
    }
}


void TitleScreen::renderGameplayState() {
    m_window.setView(m_gameplayView);

    sf::Text gameplayDebugText(m_font, sf::String("In Game Play Mode!"),  60);
    gameplayDebugText.setFillColor(sf::Color::Red);
    gameplayDebugText.setPosition({
        m_gameplayView.getCenter().x - 300,
        m_gameplayView.getCenter().y
        });
    m_window.draw(gameplayDebugText);
}

TitleButton TitleScreen::getButtonClicked(const sf::Vector2f& mousePos) {
    for (size_t i = 0; i < m_optionTexts.size(); ++i) {
       if (m_optionTexts[i].getGlobalBounds().contains(mousePos)) {
            if (m_optionStrings[i] == "새 게임") {
                return TitleButton::StartGame;
            }
            else if (m_optionStrings[i] == "게임 종료") {
                return TitleButton::ExitGame;
            }
        }
    }
    return TitleButton::None;
}
*/