#include "IntegrationLibrary.h"





int main()
{
    // 예제
    RenderWindow window(sf::VideoMode({ 600, 800 }), "Game");
    // 프레임 제한
    window.setFramerateLimit(60);

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
 
        window.display();

    }

    return 0;
}