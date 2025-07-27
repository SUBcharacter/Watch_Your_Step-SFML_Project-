// TitleScreen.cpp
#include "TitleScreen.h"
#include <iostream>

TitleScreen::TitleScreen(sf::RenderWindow& window, const std::string& backgroundTexturePath)
    : m_window(window),
    m_currentState(TITLE),
    m_backgroundSprite(nullptr),
    m_titleText(nullptr),
    m_highlightedOptionIndex(-1),
    m_keyPressClock(),
    m_keyPressDelay(sf::milliseconds(200))
{
    m_window.setFramerateLimit(60);

    initViews();
    setupTitleElements(backgroundTexturePath);
}

TitleScreen::~TitleScreen() {
    delete m_backgroundSprite;
    delete m_titleText;
    for (sf::Text& text : m_optionTexts) {
           }
    m_optionTexts.clear();
}

void TitleScreen::initViews() {
    m_titleView.setCenter({ 1200.0f / 2.0f, 900.0f / 2.0f });
    m_titleView.setSize({ 1200.0f, 900.0f });

    m_gameplayView.setCenter({ 0.0f, 0.0f });
    m_gameplayView.setSize({ 1920.0f, 1080.0f });
}
void TitleScreen::setupTitleElements(const std::string& backgroundTexturePath) {
    // 1. 배경 텍스처 로드 및 스프라이트 생성
    if (!m_backgroundTexture.loadFromFile(backgroundTexturePath)) {
        std::cerr << "오류: 배경 텍스처를 로드할 수 없습니다: " << backgroundTexturePath << std::endl;
        m_backgroundSprite = nullptr; // 로드 실패 시 nullptr로 설정
    }
    else {
        m_backgroundSprite = new sf::Sprite(m_backgroundTexture);
        float scaleX = m_titleView.getSize().x / m_backgroundTexture.getSize().x;
        float scaleY = m_titleView.getSize().y / m_backgroundTexture.getSize().y;
        m_backgroundSprite->setScale({ scaleX, scaleY });
    }

    // 2. 폰트 로드 및 타이틀 텍스트 생성
	if (!m_font.openFromFile("Assets/KoPubWorld Batang Medium.ttf" )) { // TODO: 실제 폰트 경로로 변경!
        std::cerr << "오류: 폰트를 로드할 수 없습니다. 폰트 경로를 확인하세요." << std::endl;
        m_titleText = nullptr; // 폰트 로드 실패 시 nullptr로 설정
    }
    else {
     if (m_titleText) { // 객체 생성 성공 여부 확인
            m_titleText->setFont(m_font); // 폰트 설정
            m_titleText->setString(sf::String("My Game Title")); // 텍스트 내용 설정 (sf::String 명시)
            m_titleText->setCharacterSize(80); // 글자 크기 설정
            m_titleText->setFillColor(sf::Color::Cyan); // 텍스트 색상 설정

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
    }
}
void TitleScreen::setupOptions() {
    m_optionTexts.clear();

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
                     
        update(deltaTime);
        render();
    }
}

void TitleScreen::handleTitleStateEvents(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        if (m_keyPressClock.getElapsedTime() >= m_keyPressDelay) {
            if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Up) {
                    m_highlightedOptionIndex = (m_highlightedOptionIndex - 1 + m_optionTexts.size()) % m_optionTexts.size();
                    m_keyPressClock.restart();
                }
                else if (keyEvent->code == sf::Keyboard::Key::Down) {
                    m_highlightedOptionIndex = (m_highlightedOptionIndex + 1) % m_optionTexts.size();
                    m_keyPressClock.restart();
                }
                // 엔터키 처리 부분은 나중에 구현 예정
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

    if (m_backgroundSprite) {
        m_window.draw(*m_backgroundSprite);
    }
    if (m_titleText) {
        m_window.draw(*m_titleText);
    }

    for (auto& text : m_optionTexts) {
        // text는 sf::Text& 타입, 항상 유효하므로 nullptr 체크 불필요
        m_window.draw(text);
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