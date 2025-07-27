#include "TitleScreen.h" // 자신의 헤더 파일 포함

// 표준 라이브러리 입출력
#include <iostream>      
// 문자열, 벡터 등
#include <string>        
#include <vector>
#include <algorithm> // std::min 사용 등을 위해

// TitleScreen 클래스의 생성자 구현
// 객체가 생성될 때 배경, 폰트, 텍스트, 선택지 이미지 등 모든 자원을 로드하고 초기화합니다.
TitleScreen::TitleScreen(const string& backgroundTexturePath)
{
    // --- 1. 배경 텍스처 로드 ---
    if (!backgroundTexture.loadFromFile(backgroundTexturePath))
    {
        cerr << "에러: 배경 텍스처(" << backgroundTexturePath << ")를 로드할 수 없습니다." << endl;
    }
    else // 로드 성공 시에만 스프라이트 생성
    {
        backgroundSprite.emplace(backgroundTexture); // optional 안에 sf::Sprite 생성
    }

    // --- 2. 폰트 로드 ---
    // 'openFromFile'은 'loadFromFile'로 수정. 폰트 로드 실패 시에도 메시지는 표시하지만 진행은 계속.
    if (!font.openFromFile("Assets/KoPubWorld Batang Bold.ttf"))
    {
        cerr << "에러: 폰트 (Assets/KoPubWorld Batang Bold.ttf)를 로드할 수 없습니다." << endl;
        // 폰트 로드 실패 시 텍스트 객체들을 emplace하지 않아 draw()에서 자동으로 걸러지게 됨.
    }
    else // 폰트 로드 성공 시에만 텍스트 객체들 생성 및 설정
    {
        // --- 3. 타이틀 텍스트 설정 ---
        titleText.emplace(font); // optional 안에 sf::Text 생성 (font 인자로 전달)
        titleText->setString("Welcome to the TitleScreen Screen!");
        titleText->setCharacterSize(48);
        titleText->setFillColor(Color::White);

        // --- 4. 선택지 문자열 및 이미지 경로 설정 ---
        m_optionStrings = { "게임 시작", "옵션", "나가기" };
        m_optionImagePath = {
            "Assets/TextBTN_Big.png",
            "Assets/TextBTN_Big.png",
            "Assets/TextBTN_Big.png"
        };
        m_selectedOptionIndex = 0; // 초기 선택은 첫 번째 옵션

        // --- 5. 각 선택지 텍스트 객체 생성 및 기본 설정 ---
        m_optionTexts.clear(); // 혹시 모를 이전 데이터 클리어
        for (size_t i = 0; i < m_optionStrings.size(); ++i) {
            sf::Text optionText(font); // 폰트를 인자로 전달하여 sf::Text 객체 생성
            optionText.setString(m_optionStrings[i]);
            optionText.setCharacterSize(36);      // 선택지 텍스트 크기
            optionText.setFillColor(m_defaultOptionColor); // 기본 색상
            m_optionTexts.push_back(optionText); // 벡터에 추가
        }

        // --- 6. 각 선택지 이미지 텍스처 로드 및 스프라이트 생성 ---
        m_optionImageTextures.clear(); // 벡터 클리어
        m_optionImageSprites.clear();  // 벡터 클리어

        for (const auto& path : m_optionImagePath) {
            sf::Texture texture;
            if (!texture.loadFromFile(path)) {
                cerr << "에러: 옵션 이미지(" << path << ")를 로드할 수 없습니다." << endl;
                m_optionImageTextures.emplace_back(); // 빈 텍스처 추가 (벡터 크기 유지를 위함)
                m_optionImageSprites.emplace_back(); // 빈 스프라이트 추가 (sf::Sprite 기본 생성자 오류 방지)
            }
            else {
                m_optionImageTextures.push_back(std::move(texture)); // 텍스처 이동하여 추가
                // m_optionImageTextures.back()은 벡터의 마지막 텍스처에 대한 참조를 반환합니다.
                // sf::Sprite는 Texture에 대한 참조를 저장하므로, Texture가 소멸되면 안 됩니다.
                m_optionImageSprites.emplace_back(m_optionImageTextures.back());
            }
        }
    } // End of font.loadFromFile else block
}


// run 함수: 타이틀 화면의 메인 루프를 실행하고 윈도우를 업데이트합니다.
// 이 함수는 윈도우가 열려있는 동안 화면을 표시하고 이벤트를 처리합니다.
void TitleScreen::run(sf::RenderWindow& window) // sf::RenderWindow 타입 명시
{
    // --- A. 초기 위치, 크기, 원점 설정 (이 함수 호출 시 단 한 번만 수행) ---
    sf::Vector2u windowSize = window.getSize(); // 현재 윈도우 크기 가져오기
    float centerX = static_cast<float>(windowSize.x / 2.0f);
    float centerY = static_cast<float>(windowSize.y / 2.0f);

    // 1. 배경 스프라이트 크기 및 위치 조정
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) { // 텍스처 유효성 검사
        float scaleX = static_cast<float>(windowSize.x) / backgroundTexture.getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / backgroundTexture.getSize().y;
        if (backgroundSprite.has_value()) { // optional에 값이 있는지 확인
            backgroundSprite->setScale({ scaleX, scaleY }); // 창 크기에 맞게 스케일 조정
            backgroundSprite->setPosition({ 0.f, 0.f }); // 좌상단에 배치
        }
    }

    // 2. 타이틀 텍스트 위치 및 원점 설정
    if (titleText.has_value()) { // optional에 값이 있는지 확인
        sf::FloatRect textRect = titleText->getLocalBounds();
        // 텍스트 중앙을 원점으로 설정 (SFML 3.0.0의 sf::FloatRect 멤버: position.x, position.y)
        titleText->setOrigin({ (textRect.position.x + textRect.size.x / 2.0f),
                               (textRect.position.y + textRect.size.y / 2.0f) });
        titleText->setPosition({ centerX, centerY - 150.f }); // 화면 중앙 상단에 배치
    }

    // 3. 선택지 텍스트들 위치 및 원점 설정
    float optionStartY = centerY + 50.f; // 옵션 목록 시작 Y 좌표
    for (size_t i = 0; i < m_optionTexts.size(); ++i) {
        sf::FloatRect optionRect = m_optionTexts[i].getLocalBounds();
        // 각 선택지 텍스트의 중앙을 원점으로 설정
        m_optionTexts[i].setOrigin({ (optionRect.position.x + optionRect.size.x / 2.0f),
                                     (optionRect.position.y + optionRect.size.y / 2.0f) });
        // 각 선택지 텍스트를 적절한 위치에 배치 (세로로 나열)
        m_optionTexts[i].setPosition({ centerX, optionStartY + i * 50.f });
    }

    // 4. 선택지 이미지 스프라이트들 위치 및 원점 설정
    // 각 이미지의 위치는 해당하는 텍스트의 위치 근처에 배치
    for (size_t i = 0; i < m_optionImageSprites.size(); ++i)
    {
        const sf::Texture& texture = m_optionImageSprites[i].getTexture();
        if (texture.getSize().x > 0 && texture.getSize().y > 0) {
            std::cout << "Sprite " << i << " has a valid texture. Processing..." << std::endl;
            { // optional에 값이 있는지 확인
                sf::FloatRect imageRect = m_optionImageSprites[i].getLocalBounds();
                // 이미지 중앙을 원점으로 설정
                m_optionImageSprites[i].setOrigin({ (imageRect.position.x + imageRect.size.x / 2.0f),
                                                     (imageRect.position.y + imageRect.size.y / 2.0f) });
                // 각 이미지를 해당 텍스트 옆(왼쪽 150픽셀)에 배치 (조정 필요)
                m_optionImageSprites[i].setPosition({ centerX - 150.f, optionStartY + i * 50.f });
                m_optionImageSprites[i].setScale({ 0.5f, 0.5f }); // 기본 크기 조정 (필요시)
            }
        }

        // --- B. 메인 게임 루프 ---
        while (window.isOpen()) {
            // --- 1. 이벤트 처리 ---
            while (const optional<sf::Event> eventOpt = window.pollEvent()) // SFML 3.0.0 이벤트 폴링
            {
                const sf::Event& event = *eventOpt; // optional에서 실제 sf::Event 추출

                // 전역 이벤트 (창 닫기, ESC로 종료)
                if (event.is<sf::Event::Closed>()) {
                    window.close();
                    return; // 함수 종료
                }
                else if (const auto* keypressed = event.getIf<sf::Event::KeyPressed>()) {
                    // 키 입력 딜레이 체크 (빠른 반복 입력 방지)
                    if (m_keyPressClock.getElapsedTime() < m_keyPressDelay) {
                        continue; // 딜레이 시간 내에는 입력 무시
                    }
                    m_keyPressClock.restart(); // 딜레이 클럭 재시작

                    // 방향키 처리
                    if (keypressed->scancode == sf::Keyboard::Scancode::Up) {
                        m_selectedOptionIndex = (m_selectedOptionIndex - 1 + m_optionTexts.size()) % m_optionTexts.size();
                    }
                    else if (keypressed->scancode == sf::Keyboard::Scancode::Down) {
                        m_selectedOptionIndex = (m_selectedOptionIndex + 1) % m_optionTexts.size();
                    }
                    // Enter 또는 Escape 키 입력 시 종료 (테스트용)
                    else if (keypressed->scancode == sf::Keyboard::Scancode::Enter ||
                        keypressed->scancode == sf::Keyboard::Scancode::Escape) {
                        window.close(); // 실제 게임에서는 상태 전환 로직
                        return;
                    }
                }
            }

            // --- 2. 시각적 업데이트 (매 프레임) ---
            // 선택지 텍스트 색상 및 크기 변경 (하이라이트 효과)
         // for 루프의 시작과 동일 (변경 없음)
            for (size_t i = 0; i < m_optionTexts.size(); ++i) {
                if (i == m_selectedOptionIndex) {
                    m_optionTexts[i].setFillColor(m_highlightOptionColor); // 선택된 옵션은 하이라이트 색상
                    m_optionTexts[i].setCharacterSize(40); // 선택된 것은 약간 크게

                    // m_optionImageSprites[i]가 유효한 sf::Sprite 객체이고 텍스처가 할당되어 있는지 확인
                    const sf::Texture& texture = m_optionImageSprites[i].getTexture();
                    if (texture.getSize().x > 0 && texture.getSize().y > 0) { // <-- 유효성 검사 조건
                        m_optionImageSprites[i].setColor(sf::Color::White); // 선택된 이미지는 밝게
                        m_optionImageSprites[i].setScale({ 0.6f, 0.6f });     // 약간 크게
                    }
             }
                else {
                    m_optionTexts[i].setFillColor(m_defaultOptionColor); // 선택되지 않은 옵션은 기본 색상
                    m_optionTexts[i].setCharacterSize(36); // 기본 크기

                    // m_optionImageSprites[i]가 유효한 sf::Sprite 객체이고 텍스처가 할당되어 있는지 확인
                    const sf::Texture& texture = m_optionImageSprites[i].getTexture();
                    if (texture.getSize().x > 0 && texture.getSize().y > 0) { // <-- 유효성 검사 조건
                        m_optionImageSprites[i].setColor(sf::Color(150, 150, 150)); // 약간 어둡게
                        m_optionImageSprites[i].setScale({ 0.5f, 0.5f });             // 기본 크기
                    }
                    // --- 수정 끝 ---
                }
            }

            // --- 3. 그리기 ---
            window.clear(Color::Blue); // 매 프레임마다 화면을 지우고 새로운 내용을 그립니다 (파란색으로)

            // 배경 스프라이트 그리기 (Optional 체크)
            if (backgroundSprite.has_value()) {
                window.draw(*backgroundSprite);
            }

            // 타이틀 텍스트 그리기 (Optional 체크)
            if (titleText.has_value()) {
                window.draw(*titleText);
            }

            // m_optionImageSprites가 std::vector<sf::Sprite> 타입인 경우
            for (const auto& optSprite : m_optionImageSprites) { // optSprite는 const sf::Sprite& 타입
                // 텍스처가 유효한지 확인하는 함수가 필요함
                const sf::Texture& texture = optSprite.getTexture(); // optSprite는 sf::Sprite 임
                if (texture.getSize().x > 0 && texture.getSize().y > 0) { // 텍스처가 유효한 경우에만 그림
                    window.draw(optSprite); // * 없이 바로 optSprite 그리기
                }
            }

            // 선택지 텍스트들 나중에 그리기 (이미지 위에 오도록)
            for (const auto& text : m_optionTexts) {
                window.draw(text);
            }

            window.display(); // 그린 내용을 화면에 표시
        }
    }
}