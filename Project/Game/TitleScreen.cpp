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
        cout << "에러 메세지" << endl;
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
    // 1. 배경 텍스처 로드 및 스프라이트 생성
    if (!b_texture.loadFromFile("Assets/platform.png")) {
        std::cerr << "오류: 배경 텍스처를 로드할 수 없습니다: " << b_textureP << std::endl;     
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
        std::cerr << "오류: 지시자 텍스처를 로드할 수 없습니다: Assets/player.png" << std::endl;
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
        std::cerr << "시작 버튼 이미지 로드 실패!" << std::endl;
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
        std::cerr << "종료 버튼 이미지 로드 실패!" << std::endl;
      }

    if (!m_optionBtns.empty()) {
        m_selIdx = 0; //
    }
    else {
        m_selIdx = -1;
    }
}

void TitleScreen::initGPElems() {
    std::cout << "게임 플레이 요소들이 초기화되었습니다!" << std::endl;
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

            // 키보드, 마우스 이동, 마우스 버튼 누름 이벤트가 발생했을 경우
            if constexpr (std::is_same_v<T, sf::Event::KeyPressed> ||
                std::is_same_v<T, sf::Event::MouseMoved> ||
                std::is_same_v<T, sf::Event::MouseButtonPressed>) {
                // 게임의 현재 상태(TITLE 또는 GAMEPLAY)에 따라 다른 이벤트 핸들러 호출
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
                    m_selIdx = (m_selIdx == 0) ? static_cast<int>(numButtons - 1) : m_selIdx - 1; // m_selIdx: 헤더와 동일. (m_selIdx - 1 + numButtons) % numButtons; 대신 if/else로 처리하면 -1 초기값 문제 피할 수 있음
                    m_keyClk.restart();
                }
                else if (keyEv->code == sf::Keyboard::Key::Down) {
                    m_selIdx = (m_selIdx == static_cast<int>(numButtons - 1)) ? 0 : m_selIdx + 1; // m_selIdx: 헤더와 동일
                    m_keyClk.restart();
                }
                else if (keyEv->code == sf::Keyboard::Key::Enter) {
                    if (m_selIdx >= 0 && m_selIdx < static_cast<int>(numButtons)) {
                        if (m_selIdx == 0) {
                            m_state = GAMEPLAY; 
                            initGPElems(); 
                            m_window.setView(m_gameV); 
                            std::cout << "새 게임 이미지 버튼 선택!" << std::endl;
                        }
                        else if (m_selIdx == 1) { 
                            m_window.close(); 
                            std::cout << "게임 종료 이미지 버튼 선택!" << std::endl;
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
    // 마우스 이벤트 처리 
    else if (event.is<sf::Event::MouseMoved>()) {
        Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window), m_titleV); // m_window, m_titleV: 헤더와 동일

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
                Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window), m_titleV); // m_window, m_titleV: 헤더와 동일

                TitleButton clickedBtn = getBtnClicked(mousePos); // getBtnClicked: 헤더와 동일
                if (clickedBtn == TitleButton::StartGame) {
                    m_state = GAMEPLAY; // m_state: 헤더와 동일
                    initGPElems(); // initGPElems: 헤더와 동일
                    m_window.setView(m_gameV); // m_window, m_gameV: 헤더와 동일
                    std::cout << "마우스로 새 게임 시작! 게임플레이 모드로 전환합니다." << std::endl;
                }
                else if (clickedBtn == TitleButton::ExitGame) {
                    m_window.close(); // m_window: 헤더와 동일
                    std::cout << "마우스로 게임 종료." << std::endl;
                }
            }
        }
    }
}


void TitleScreen::h_GameEvs(const Event& event) { // h_GameEvs: 헤더와 동일
    if (event.is<sf::Event::KeyPressed>()) {
        if (auto keyEv = event.getIf<sf::Event::KeyPressed>()) {
            if (keyEv->code == sf::Keyboard::Key::Escape) {
                std::cout << "게임플레이 중 Escape 키 눌림." << std::endl;
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
    // 타이틀 화면은 정적이므로 별도 업데이트 없음
}

void TitleScreen::updateGameplayState(float deltaTime) {
    // TODO: 게임 플레이 로직 업데이트
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
    return TitleButton::None; // 기본 반환값
}