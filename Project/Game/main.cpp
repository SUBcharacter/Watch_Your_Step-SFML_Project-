#include "IntegrationLibrary.h"

#include "Game_Manager.h"


enum class mainstate
{
    Title,
	MainMenu,
    mainPlay,
    Playing,
    Paused,
	Exit
    //mainOver
};
mainstate currentState = mainstate::Title;

=======
    // ¿¹Á¦
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }



//int main()
//{
//    Game_Manager game_manager;
//    game_manager.run();
//    return 0;
//} 변경한건 우선 주석처리해서 올립니다.
// 