#include "IntegrationLibrary.h"
#include "Physics.h"
int main()
{
    // 예제
    RenderWindow window(sf::VideoMode({ 800, 600 }), "Game");
    // 프레임 제한
    window.setFramerateLimit(60);

    // 물리 객체 생성
    Physics physics;

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


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
        {
            physics.playerx -= 2;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
        {
            physics.playerx += 2;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
            physics.Jump();
        }

        // 충돌 체크
        physics.Collision();

        // 플레이어 그리기용
        sf::RectangleShape player(sf::Vector2f(physics.playerw, physics.playerh));
        player.setPosition({ static_cast<float>(physics.playerx), static_cast<float>(physics.playery) });
        player.setFillColor(sf::Color::Blue);

        // 플랫폼 그리기용 
        sf::RectangleShape platform(sf::Vector2f(physics.platformw, physics.platformh));
        platform.setPosition({ static_cast<float>(physics.platformx), static_cast<float>(physics.platformy) });
        platform.setFillColor(sf::Color::Green);

        // 화면 그리기
        window.clear(sf::Color::Black);
        window.draw(player);
        window.draw(platform);
        window.display();
    }

    return 0;
}