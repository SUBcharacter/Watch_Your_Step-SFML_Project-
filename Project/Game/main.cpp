#include "IntegrationLibrary.h"
#include "Physics.h"
#include "Platform.h"
int main()
{
    // 예제
    RenderWindow window(sf::VideoMode({ 600, 800 }), "Game");
    // 프레임 제한
    window.setFramerateLimit(60);

    // 물리 객체 생성
    Physics physics;

    Platform* pl = new Platform(300, 0, 52, 52);
    pl->SetPosition(300.f,300.f);
    
    // 메인 루프
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            //창 닫기 버튼을 눌렀을 경우
            if (event->is<sf::Event::Closed>())
            {
                // 창 닫기
                window.close();
            }
            //키보드 키가 눌렀을 경우 처리
            else if (const auto* keypressed = event->getIf < sf::Event::KeyPressed>())
            {
                // Esc를 눌렀을 경우 창 닫기
                if (keypressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
        }
        window.clear();
        pl->Draw(window);
        window.display();
        
    }

    return 0;
}