// TitleScreen.cpp
#include "TitleScreen.h"
#include <iostream>

TitleScreen::TitleScreen(sf::RenderWindow& window, const std::string& b_textureP)
    : m_window(window),
    m_state(TITLE),
    b_Sprite(b_texture),
    m_selIdx(0),
    m_keyClk(),
    m_keyDly(sf::milliseconds(200))    
{
    m_window.setFramerateLimit(60);

    if (!b_texture.loadFromFile(""))
    {
        cout << "���� �޼���" << endl;
    }
    b_Sprite.setTexture(b_texture);
    b_Sprite.setOrigin({600.0f, 400.0f});
    b_Sprite.setPosition({ 600.f, 400.0f });
    initViews();
    setupElements(b_textureP);
    setupOptions();
}

TitleScreen::~TitleScreen() {
    
 
}

void TitleScreen::initViews() {
    m_titleV.setCenter({ 1200.0f / 2.0f, 800.0f / 2.0f });
    m_titleV.setSize({ 1200.0f, 800.0f });

    m_gameV.setCenter({ 0.0f, 0.0f });
    m_gameV.setSize({ 1920.0f, 1080.0f });
}
void TitleScreen::setupElements(const std::string& b_textureP) {
    // 1. ��� �ؽ�ó �ε� �� ��������Ʈ ����
    if (!b_texture.loadFromFile("Assets/platform.png")) {
        std::cerr << "����: ��� �ؽ�ó�� �ε��� �� �����ϴ�: " << b_textureP << std::endl;     
    }
    else {
        b_Sprite.setTexture(b_texture);
        float scaleX = m_titleV.getSize().x / b_texture.getSize().x;
        float scaleY = m_titleV.getSize().y / b_texture.getSize().y;
        b_Sprite.setScale({ scaleX, scaleY });

        sf::FloatRect bounds = b_Sprite.getLocalBounds();
        b_Sprite.setOrigin({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });
        b_Sprite.setPosition({ m_titleV.getCenter().x, m_titleV.getCenter().y });

    }
    if (!m_indTex.loadFromFile("Assets/player.png")) {
        std::cerr << "����: ������ �ؽ�ó�� �ε��� �� �����ϴ�: Assets/player.png" << std::endl;
    }
    else {
        m_indSpr.setTexture(m_indTex);
        sf::FloatRect indicatorRect = m_indSpr.getLocalBounds();
        m_indSpr.setOrigin({ indicatorRect.position.x + indicatorRect.size.x, indicatorRect.position.y + indicatorRect.size.y / 2.0f });
        m_indSpr.setScale({ 0.5f, 0.5f }); 
    }
}
void TitleScreen::setupOptions() {
   
    m_optionBtns.clear(); 
    sf::Texture startBtnTex;
    if (startBtnTex.loadFromFile("Assets/start_button.png")) {
        Sprite startBtn(startBtnTex);
        startBtn.setOrigin({ startBtn.getLocalBounds().position.x + startBtn.getLocalBounds().size.x / 2.0f,
                            startBtn.getLocalBounds().position.y + startBtn.getLocalBounds().size.y / 2.0f });
        startBtn.setPosition({ m_titleV.getCenter().x, m_titleV.getCenter().y + 80.0f }); // m_titleView -> m_titleV
        m_optionBtns.push_back(startBtn);
    }
    else {
        std::cerr << "���� ��ư �̹��� �ε� ����!" << std::endl;
    }
    sf::Texture exitBtnTex;
    if (exitBtnTex.loadFromFile("Assets/exit_button.png")) { 
        Sprite exitBtn(exitBtnTex);
        exitBtn.setOrigin({ exitBtn.getLocalBounds().position.x + exitBtn.getLocalBounds().size.x / 2.0f,
                           exitBtn.getLocalBounds().position.y + exitBtn.getLocalBounds().size.y / 2.0f });
        exitBtn.setPosition({ m_titleV.getCenter().x, m_titleV.getCenter().y + 80.0f + 80.0f });
        m_optionBtns.push_back(exitBtn);
    }
    else {
        std::cerr << "���� ��ư �̹��� �ε� ����!" << std::endl;
      }

    if (!m_optionBtns.empty()) {
        m_selIdx = 0; //
    }
    else {
        m_selIdx = -1;
    }
}

void TitleScreen::initGPElems() {
    std::cout << "���� �÷��� ��ҵ��� �ʱ�ȭ�Ǿ����ϴ�!" << std::endl;
}

void TitleScreen::run() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        handleEvs();  
        update(deltaTime);
        render();
    }
}

void TitleScreen::handleEvs() { 
    while (true) { 
        auto eventOpt = m_window.pollEvent();

        if (!eventOpt.has_value()) {
            break;
        }
        sf::Event& event = eventOpt.value(); 
        if (event.is<sf::Event::Closed>()) {
            m_window.close(); 
        }

        event.visit([&](auto& current_ev) { 
            using T = std::decay_t<decltype(current_ev)>; 

            // Ű����, ���콺 �̵�, ���콺 ��ư ���� �̺�Ʈ�� �߻����� ���
            if constexpr (std::is_same_v<T, sf::Event::KeyPressed> ||
                std::is_same_v<T, sf::Event::MouseMoved> ||
                std::is_same_v<T, sf::Event::MouseButtonPressed>) {
                // ������ ���� ����(TITLE �Ǵ� GAMEPLAY)�� ���� �ٸ� �̺�Ʈ �ڵ鷯 ȣ��
                if (m_state == TITLE) {
                    h_TitleEvs(event);
                }
                else if (m_state == GAMEPLAY) { 
                    h_GameEvs(event); 
                }
            }
            });
    }
}


void TitleScreen::h_TitleEvs(const Event& event) { 
    if (event.is<sf::Event::KeyPressed>()) {
        if (m_keyClk.getElapsedTime() >= m_keyDly) { 
            if (auto keyEv = event.getIf<sf::Event::KeyPressed>()) { 
                const size_t numButtons = m_optionBtns.size();
                if (numButtons == 0) return; 

                if (keyEv->code == sf::Keyboard::Key::Up) {
                    m_selIdx = (m_selIdx == 0) ? static_cast<int>(numButtons - 1) : m_selIdx - 1; // m_selIdx: ����� ����. (m_selIdx - 1 + numButtons) % numButtons; ��� if/else�� ó���ϸ� -1 �ʱⰪ ���� ���� �� ����
                    m_keyClk.restart();
                }
                else if (keyEv->code == sf::Keyboard::Key::Down) {
                    m_selIdx = (m_selIdx == static_cast<int>(numButtons - 1)) ? 0 : m_selIdx + 1; // m_selIdx: ����� ����
                    m_keyClk.restart();
                }
                else if (keyEv->code == sf::Keyboard::Key::Enter) {
                    if (m_selIdx >= 0 && m_selIdx < static_cast<int>(numButtons)) {
                        if (m_selIdx == 0) {
                            m_state = GAMEPLAY; 
                            initGPElems(); 
                            m_window.setView(m_gameV); 
                            std::cout << "�� ���� �̹��� ��ư ����!" << std::endl;
                        }
                        else if (m_selIdx == 1) { 
                            m_window.close(); 
                            std::cout << "���� ���� �̹��� ��ư ����!" << std::endl;
                        }
                    }
                }
                else if (keyEv->code == sf::Keyboard::Key::Escape) {
                    m_window.close();
                    return;
                }
            }
        }
    }
    // ���콺 �̺�Ʈ ó�� 
    else if (event.is<sf::Event::MouseMoved>()) {
        Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window), m_titleV); // m_window, m_titleV: ����� ����

        int prevSelIdx = m_selIdx; 
        m_selIdx = -1; 

        for (size_t i = 0; i < m_optionBtns.size(); ++i) {  
            if (m_optionBtns[i].getGlobalBounds().contains(mousePos)) { 
                m_selIdx = static_cast<int>(i); 
                break;
            }
        }
        
    }
    else if (event.is<sf::Event::MouseButtonPressed>()) {
        if (auto mouseBtnEv = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseBtnEv->button == sf::Mouse::Button::Left) {
                Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window), m_titleV); // m_window, m_titleV: ����� ����

                TitleButton clickedBtn = getBtnClicked(mousePos); // getBtnClicked: ����� ����
                if (clickedBtn == TitleButton::StartGame) {
                    m_state = GAMEPLAY; // m_state: ����� ����
                    initGPElems(); // initGPElems: ����� ����
                    m_window.setView(m_gameV); // m_window, m_gameV: ����� ����
                    std::cout << "���콺�� �� ���� ����! �����÷��� ���� ��ȯ�մϴ�." << std::endl;
                }
                else if (clickedBtn == TitleButton::ExitGame) {
                    m_window.close(); // m_window: ����� ����
                    std::cout << "���콺�� ���� ����." << std::endl;
                }
            }
        }
    }
}


void TitleScreen::h_GameEvs(const Event& event) { // h_GameEvs: ����� ����
    if (event.is<sf::Event::KeyPressed>()) {
        if (auto keyEv = event.getIf<sf::Event::KeyPressed>()) {
            if (keyEv->code == sf::Keyboard::Key::Escape) {
                std::cout << "�����÷��� �� Escape Ű ����." << std::endl;
            }
        }
    }
}

/////////////////////////

void TitleScreen::update(float deltaTime) {
    switch (m_state) {
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

    switch (m_state) {
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
    m_window.setView(m_titleV);

    if (b_Sprite) {
        m_window.draw(b_Sprite);
    }
 
    if (m_selIdx >= 0 && m_selIdx < m_optionTexts.size() && m_indTex.getSize().x > 0) {
        sf::Text& highlightedText = m_optionTexts[m_selIdx];
        sf::FloatRect textBounds = highlightedText.getGlobalBounds();
            
        m_indSpr.setPosition({
       textBounds.position.x - m_indSpr.getGlobalBounds().size.x - 20.0f,
       textBounds.position.y + textBounds.size.y / 2.0f - m_indSpr.getGlobalBounds().size.y / 2.0f
            });
        m_window.draw(m_indSpr);
    }
}


void TitleScreen::renderGameplayState() {
    m_window.setView(m_gameV);

    sf::Text gameplayDebugText(m_font, sf::String("In Game Play Mode!"),  60);
    gameplayDebugText.setFillColor(sf::Color::Red);
    gameplayDebugText.setPosition({
        m_gameV.getCenter().x - 300,
        m_gameV.getCenter().y
        });
    m_window.draw(gameplayDebugText);
}

TitleButton TitleScreen::getButtonClicked(const sf::Vector2f& mousePos) {
        if (m_startButtonSprite.getGlobalBounds().contains(mousePos)) return TitleButton::StartGame;
      else if (m_exitButtonSprite.getGlobalBounds().contains(mousePos)) return TitleButton::ExitGame;
    return TitleButton::None; // �⺻ ��ȯ��
}