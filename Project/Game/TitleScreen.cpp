// TitleScreen.cpp

#include "TitleScreen.h"
#include <iostream>

// SFML의 Vector2f를 사용하기 위해 필요 (IntegrationLibrary.h에 포함되어 있지 않다면)
// #include <SFML/System/Vector2.hpp>

TitleScreen::TitleScreen(int left, int top, int width, int height)
    : m_left(left), m_top(top), m_width(width), m_height(height),
    m_selectedButtonIndex(0)
{
    loadAssets();

    m_buttons.push_back(&startButton);
    m_buttons.push_back(&exitButton);

    updateButtonSelection();
}
//칸에 직접 숫자 넣어서 실행해보기 및 오류 정리
void TitleScreen::loadAssets() {
    // 배경 이미지 로드
    // 예시: TitleScreen.cpp 내 loadAssets() 일부

// 타이틀 화면 영역을 IntRect로 정의
sf::IntRect rectI = { m_left, m_top, m_width, m_height };

// IntRect의 position과 size를 FloatRect로 변환 (static_cast 활용)
sf::FloatRect rectF = {
    { static_cast<float>(rectI.left), static_cast<float>(rectI.top) },
    { static_cast<float>(rectI.width), static_cast<float>(rectI.height) }
};

// 배경 텍스처 설정
backSprite.setTexture(backTexture);
backSprite.setTextureRect(rectI); // 텍스처에서 사용할 영역 지정
backSprite.setPosition(static_cast<sf::Vector2f>(rectF.position)); // 위치 설정
backSprite.setScale(
    rectF.width / static_cast<float>(backTexture.getSize().x),
    rectF.height / static_cast<float>(backTexture.getSize().y)
);

// 로고 위치 설정 (중앙 정렬)
logoSprite.setTexture(logoTexture);
logoSprite.setOrigin(
    static_cast<float>(logoTexture.getSize().x) / 2.f,
    static_cast<float>(logoTexture.getSize().y) / 2.f
);
logoSprite.setPosition(
    rectF.left + rectF.width / 2.f,
    rectF.top + rectF.height / 4.f
);

// 버튼 위치도 비슷하게 설정
startButton.setOrigin(
    startButton.getLocalBounds().width / 2.f,
    startButton.getLocalBounds().height / 2.f
);
startButton.setPosition(
    rectF.left + rectF.width / 2.f,
    rectF.top + rectF.height / 2.f + 50.f
);

exitButton.setOrigin(
    exitButton.getLocalBounds().width / 2.f,
    exitButton.getLocalBounds().height / 2.f
);
exitButton.setPosition(
    rectF.left + rectF.width / 2.f,
    startButton.getPosition().y + 100.f
);

    // TODO: 배경 음악 로드 및 재생 (선택 사항)
    // if (!m_bgMusic.openFromFile("assets/bg_music.ogg")) { ... }
    // m_bgMusic.setLoop(true);
    // m_bgMusic.play();
}

void TitleScreen::handleEvent(const sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        m_finished = true;
        m_nextState = GameState::Exiting;
    }
    else if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
            m_finished = true;
            m_nextState = GameState::Exiting;
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {
            m_selectedButtonIndex = (m_selectedButtonIndex - 1 + m_buttons.size()) % m_buttons.size();
            updateButtonSelection();
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
            m_selectedButtonIndex = (m_selectedButtonIndex + 1) % m_buttons.size();
            updateButtonSelection();
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
            activateSelectedButton();
        }
    }
    // 마우스 클릭 이벤트 (m_window 참조가 없으므로 주석 처리 또는 외부에서 window.mapPixelToCoords 사용)
    // 현재 TitleScreen은 RenderWindow를 멤버로 가지지 않으므로, 이 부분을 처리하려면
    // run() 함수에서 window를 handleEvent로 전달하거나, handleEvent에서 직접 window를 매개변수로 받아야 합니다.
    // 여기서는 키보드 입력에 집중하기 위해 마우스 클릭 로직은 잠시 제외합니다.
    /*
    else if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Left) {
            // 이 부분은 TitleScreen이 window 참조를 가지고 있지 않으므로 수정이 필요합니다.
            // sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
            // if (isButtonClicked(startButton, mousePos)) { ... }
        }
    }
    */
}

void TitleScreen::update(float deltaTime) {
    // 현재는 버튼 선택에 따른 시각적 피드백이 updateButtonSelection()에서 처리되므로,
    // 추가적인 동적 업데이트 로직이 필요할 때 구현합니다.
}

void TitleScreen::draw(sf::RenderWindow& window) {
    window.clear();

    window.draw(backSprite);
    window.draw(logoSprite);
    window.draw(startButton);
    window.draw(exitButton);

    window.display();
}

void TitleScreen::updateButtonSelection() {
    for (sf::Text* button : m_buttons) {
        button->setFillColor(sf::Color::White);
    }
    if (!m_buttons.empty()) {
        m_buttons[m_selectedButtonIndex]->setFillColor(sf::Color::Red); // 선택된 버튼 강조
    }
}

void TitleScreen::activateSelectedButton() {
    if (m_selectedButtonIndex == 0) { // 시작 버튼
        std::cout << "Start Game (현재는 종료됩니다)" << std::endl;
        m_finished = true;
        m_nextState = GameState::Exiting; // 미완성 화면이므로 임시로 종료 상태로 전환
    }
    else if (m_selectedButtonIndex == 1) { // 종료 버튼
        std::cout << "Exit Game" << std::endl;
        m_finished = true;
        m_nextState = GameState::Exiting;
    }
}

bool TitleScreen::isButtonClicked(const sf::Text& button, const sf::Vector2f& mousePos) {
    // 이 함수는 현재 마우스 클릭 로직이 주석 처리되어 사용되지 않습니다.
    // 마우스 클릭 기능을 다시 활성화하려면, 이 함수가 window 참조를 받을 수 있도록 수정해야 합니다.
    return button.getGlobalBounds().contains(mousePos);
}

GameState TitleScreen::run(sf::RenderWindow& window) {
    sf::Clock clock;

    // TODO: 배경 음악 재생 시작 (선택 사항)
    // m_bgMusic.play();

    while (window.isOpen() && !m_finished) {
        float deltaTime = clock.restart().asSeconds();

        while (const std::optional<sf::Event> eventOpt = window.pollEvent()) {
            handleEvent(*eventOpt);
        }

        update(deltaTime);
        draw(window);
    }

    // TODO: 배경 음악 정지 (선택 사항)
    // m_bgMusic.stop();

    return m_nextState;
}