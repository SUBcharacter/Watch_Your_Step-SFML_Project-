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
    // 1. ��� �ؽ�ó �ε� �� ��������Ʈ ����
    if (!m_backgroundTexture.loadFromFile(backgroundTexturePath)) {
        std::cerr << "����: ��� �ؽ�ó�� �ε��� �� �����ϴ�: " << backgroundTexturePath << std::endl;
        m_backgroundSprite = nullptr; // �ε� ���� �� nullptr�� ����
    }
    else {
        m_backgroundSprite = new sf::Sprite(m_backgroundTexture);
        float scaleX = m_titleView.getSize().x / m_backgroundTexture.getSize().x;
        float scaleY = m_titleView.getSize().y / m_backgroundTexture.getSize().y;
        m_backgroundSprite->setScale({ scaleX, scaleY });
    }

    // 2. ��Ʈ �ε� �� Ÿ��Ʋ �ؽ�Ʈ ����
	if (!m_font.openFromFile("Assets/KoPubWorld Batang Medium.ttf" )) { // TODO: ���� ��Ʈ ��η� ����!
        std::cerr << "����: ��Ʈ�� �ε��� �� �����ϴ�. ��Ʈ ��θ� Ȯ���ϼ���." << std::endl;
        m_titleText = nullptr; // ��Ʈ �ε� ���� �� nullptr�� ����
    }
    else {
     if (m_titleText) { // ��ü ���� ���� ���� Ȯ��
            m_titleText->setFont(m_font); // ��Ʈ ����
            m_titleText->setString(sf::String("My Game Title")); // �ؽ�Ʈ ���� ���� (sf::String ���)
            m_titleText->setCharacterSize(80); // ���� ũ�� ����
            m_titleText->setFillColor(sf::Color::Cyan); // �ؽ�Ʈ ���� ����

            // �ؽ�Ʈ ���� �� ��ġ ���� (���� ������ ����)
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
    std::cout << "���� �÷��� ��ҵ��� �ʱ�ȭ�Ǿ����ϴ�!" << std::endl;
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
                // ����Ű ó�� �κ��� ���߿� ���� ����
            }
        }
    }
}

void TitleScreen::handleGameplayStateEvents(const sf::Event& event) {
    // TODO: ���� �÷��� �̺�Ʈ ó��
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
    // Ÿ��Ʋ ȭ���� �����̹Ƿ� ���� ������Ʈ ����
}

void TitleScreen::updateGameplayState(float deltaTime) {
    // TODO: ���� �÷��� ���� ������Ʈ
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
        // text�� sf::Text& Ÿ��, �׻� ��ȿ�ϹǷ� nullptr üũ ���ʿ�
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
            if (m_optionStrings[i] == "�� ����") {
                return TitleButton::StartGame;
            }
            else if (m_optionStrings[i] == "���� ����") {
                return TitleButton::ExitGame;
            }
        }
    }
    return TitleButton::None;
}