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
{  //<-���⼭ '"sf::Sprite" Ŭ������ �⺻ �����ڰ� �����ϴ�.'���������� ����� Ȯ�� ���߽��ϴ�.
    m_window.setFramerateLimit(60);

    if (!b_texture.loadFromFile(""))
    {
        cout << "���� �޼���" << endl;
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
    // 1. ��� �ؽ�ó �ε� �� ��������Ʈ ����
    if (!b_texture.loadFromFile("Assets/platform.png")) {
        std::cerr << "����: ��� �ؽ�ó�� �ε��� �� �����ϴ�: " << backgroundTexturePath << std::endl;
        b_Sprite = nullptr; 
       
    }
    else {
        if (b_Sprite) { delete b_Sprite; }
        b_Sprite = new sf::Sprite(b_texture);
        float scaleX = m_titleView.getSize().x / b_texture.getSize().x;
        float scaleY = m_titleView.getSize().y / b_texture.getSize().y;
        b_Sprite.setScale({ scaleX, scaleY });
    }

    // 2. ��Ʈ �ε� �� Ÿ��Ʋ �ؽ�Ʈ ����
	if (!m_font.openFromFile("Assets/KoPubWorld Batang Medium.ttf" )) { // TODO: ���� ��Ʈ ��η� ����!
        std::cerr << "����: ��Ʈ�� �ε��� �� �����ϴ�. ��Ʈ ��θ� Ȯ���ϼ���." << std::endl;
        m_titleText = nullptr; 
    }
    else {
        if (m_titleText) { delete m_titleText; }

        m_titleText = new sf::Text(m_font, sf::String("My Game Title"), 80);
        m_titleText->setFillColor(sf::Color::White); // �ؽ�Ʈ ���� ����

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
    if (!m_indicatorTexture.loadFromFile("Assets/player.png")) {
        std::cerr << "����: ������ �ؽ�ó�� �ε��� �� �����ϴ�: Assets/player.png" << std::endl;
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
        std::cerr << "���: ��Ʈ�� �ε���� �ʾ� �ɼ� �ؽ�Ʈ�� ������ �� �����ϴ�." << std::endl;
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
    std::cout << "���� �÷��� ��ҵ��� �ʱ�ȭ�Ǿ����ϴ�!" << std::endl;
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

        sf::Event& event = eventOpt.value(); // �̺�Ʈ ��ü ����

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
                // ����Ű ó�� �κ��� ���߿� ���� ����
                
                }

                else if (keyEvent->code == sf::Keyboard::Key::Escape) {
                  m_window.close();
                    return;
                }
            }
        }
    }
    else if (event.is<sf::Event::MouseMoved>()) {
        // ���콺 �̵� �� ���̶���Ʈ ���� ���� (���� ���콺 ��ġ�� ����Ͽ� ó��)
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
        // ���̶���Ʈ ���� �� ȿ���� ���� ����� �� ���� (prevHighlightedIndex�� ��)
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
                    std::cout << "���콺�� �� ���� ����! �����÷��� ���� ��ȯ�մϴ�." << std::endl;
                }
                else if (clickedButton == TitleButton::ExitGame) {
                    m_window.close(); // ���� ����
                    std::cout << "���콺�� ���� ����." << std::endl;
                }
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

    if (b_Sprite) {
        m_window.draw(*b_Sprite);
    }
    if (m_titleText) {
        m_window.draw(*m_titleText);
    }
    for (size_t i = 0; i < m_optionTexts.size(); ++i) {//�޴�
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
*/