#include "TitleScreen.h"
#include <iostream> // 에러 메시지 출력을 위해 포함 (std::cerr 사용)

// 생성자 구현
TitleScreen::TitleScreen(const std::string& backgroundTexturePath)
 : backgroundTexture(), // 기본 생성자로 먼저 생성
font()
{
    // 1. 배경 텍스처 로드
    if (!backgroundTexture.loadFromFile(backgroundTexturePath))
    {
        std::cerr << "에러: 배경 스프라이트(" << backgroundTexturePath << ")를 찾을 수 없습니다." << std::endl;
        // 실제 애플리케이션에서는 여기서 에러 처리 로직을 추가해야 합니다.
    }
    // 배경 스프라이트에 텍스처 설정 (위치/크기 조정은 run()에서 윈도우 크기 기반으로 수행)
    backgroundSprite.setTexture(backgroundTexture);

    // 2. 폰트 로드
    // 폰트 파일 경로에 확장자(.ttf, .otf 등)를 정확히 명시해야 합니다.
    if (!font.openFromFile("Assets/KoPubWorld_Batang_Bold.ttf")) // 예시: .ttf 확장자 사용
    {
        std::cerr << "에러: 폰트 (Assets/KoPubWorld Batang Bold.ttf)를 찾을 수 없습니다." << std::endl;
        // 실제 애플리케이션에서는 여기서 에러 처리 로직을 추가해야 합니다.
    }

    // 3. 타이틀 텍스트 초기 설정 (폰트, 문자열, 크기, 색상)
    titleText.setFont(font);
    titleText.setString("Welcome to the TitleScreen Screen!");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    // 텍스트 위치 설정은 run()에서 윈도우 크기 기반으로 수행합니다.
}

// run() 함수 구현
void TitleScreen::run(sf::RenderWindow& window) // sf::RenderWindow를 참조로 받음
{
    // 윈도우의 현재 크기를 가져옵니다.
    sf::Vector2u windowSize = window.getSize();

   // // 배경 스프라이트 크기 조정 (윈도우 크기에 맞춤)
   // // 텍스처 크기가 0일 경우 나눗셈 오류 방지를 위해 체크합니다.
   // if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) {
   //     float scaleX = static_cast<float>(windowSize.x) / backgroundTexture.getSize().x;
   //     float scaleY = static_cast<float>(windowSize.y) / backgroundTexture.getSize().y;
   //     backgroundSprite.setScale(scaleX, scaleY);
   // }
   // backgroundSprite.setPosition(0.f, 0.f); // 배경은 창의 왼쪽 상단에 배치
   //
   // // 타이틀 텍스트를 창의 중앙에 위치시키기 위한 원점(origin) 설정 및 위치 조정
   // sf::FloatRect textRect = titleText.getLocalBounds();
   // titleText.setOrigin(textRect.left + textRect.width / 2.0f,
   //     textRect.top + textRect.height / 2.0f);
   // titleText.setPosition(static_cast<float>(windowSize.x / 2.0f),
   //     static_cast<float>(windowSize.y / 2.0f));

    // 메인 루프: 윈도우가 열려있는 동안 타이틀 화면을 표시
    while (window.isOpen()) {
        // 이벤트 폴링 (main 함수의 스타일을 따릅니다)
        while (const std::optional event = window.pollEvent())
        {
            // 창 닫기 버튼을 눌렀을 경우
            if (event->is<sf::Event::Closed>())
            {
                window.close(); // 창 닫기
                return; // 타이틀 화면 루프 종료
            }
            // 키보드 키가 눌렸을 경우 처리
            else if (const auto* keypressed = event->getIf < sf::Event::KeyPressed>())
            {
                // Enter 또는 Escape를 눌렀을 경우 타이틀 화면 종료
                if (keypressed->scancode == sf::Keyboard::Scancode::Enter ||
                    keypressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    return; // 타이틀 화면 루프 종료 (창은 닫지 않고 메인 루프로 넘어감)
                }
            }
        }

        // 창을 지웁니다.
        window.clear(sf::Color::Black);

        // 1. 배경 스프라이트를 먼저 그립니다.
        window.draw(backgroundSprite);

        // 2. 그 위에 타이틀 텍스트를 그립니다.
        window.draw(titleText);

        // 화면에 그린 내용을 표시합니다.
        window.display();
    }
}