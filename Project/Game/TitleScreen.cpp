#include "TitleScreen.h"

// 생성자 구현
// 멤버 초기화 리스트를 사용하여 backgroundTexture, font를 먼저 로드하고
// 그 다음 backgroundSprite와 titleText를 초기화합니다.
TitleScreen::TitleScreen(const string& backgroundTexturePath) : backgroundSprite(backgroundTexture), titleText(font)
// 멤버 초기화 리스트 시작
// backgroundTexture 로드 // 기본 생성자로 먼저 생성
     // 기본 생성자로 먼저 생성
{
    // 1. 배경 텍스처 로드 (생성자 본문에서 로드)
    if (!backgroundTexture.loadFromFile(backgroundTexturePath))
    {
        cerr << "에러: 배경 스프라이트(" << backgroundTexturePath << ")를 찾을 수 없습니다." << endl;
        // 에러 처리 로직
    }
    // 이제 backgroundTexture가 유효하므로 backgroundSprite에 설정합니다.
    backgroundSprite.setTexture(backgroundTexture); // 여기서 setTexture 호출

    // 2. 폰트 로드 (생성자 본문에서 로드)
    if (!font.openFromFile("Assets/KoPubWorld Batang Bold.ttf")) // 정확한 폰트 경로와 확장자 확인
    {
        cerr << "에러: 폰트 (Assets/KoPubWorld Batang Bold.ttf)를 찾을 수 없습니다." << endl;
        // 에러 처리 로직
    }
    // 이제 font가 유효하므로 titleText에 설정합니다.
    titleText.setFont(font); // 여기서 setFont 호출

    // 3. 타이틀 텍스트의 나머지 설정
    titleText.setString("Welcome to the TitleScreen Screen!");
    titleText.setCharacterSize(48);
    titleText.setFillColor(Color::White);
}

// run() 함수는 이전과 동일합니다.
void TitleScreen::run(RenderWindow& window)
{
   // // 윈도우의 현재 크기를 가져옵니다.
   sf::Vector2u windowSize = window.getSize();
   
   // 배경 스프라이트 크기 조정 (윈도우 크기에 맞춤)
   if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) {
       float scaleX = static_cast<float>(windowSize.x) / backgroundTexture.getSize().x;
       float scaleY = static_cast<float>(windowSize.y) / backgroundTexture.getSize().y;
       backgroundSprite.setScale({ scaleX, scaleY });
   }
   backgroundSprite.setPosition({ 0.f, 0.f }); // 배경은 창의 왼쪽 상단에 배치
   
   // 타이틀 텍스트를 창의 중앙에 위치시키기 위한 원점(origin) 설정 및 위치 조정
   sf::FloatRect textRect = titleText.getLocalBounds();
   titleText.setOrigin({ (textRect.position.x + textRect.size.x / 2.0f), (textRect.position.y + textRect.size.y / 2.0f )});
   titleText.setPosition({ static_cast<float>(windowSize.x / 2.0f),
       static_cast<float>(windowSize.y / 2.0f) });

    // 메인 루프: 윈도우가 열려있는 동안 타이틀 화면을 표시
    while (window.isOpen()) {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
                return;
            }
            else if (const auto* keypressed = event->getIf < Event::KeyPressed>())
            {
                if (keypressed->scancode == Keyboard::Scancode::Enter ||
                    keypressed->scancode == Keyboard::Scancode::Escape)
                {
                    return;
                }
            }
        }

        window.clear(Color::Black);
        window.draw(backgroundSprite);
        window.draw(titleText);
        window.display();
    }
}