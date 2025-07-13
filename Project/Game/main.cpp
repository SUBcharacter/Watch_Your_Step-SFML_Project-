#include "IntegrationLibrary.h"
#include "Player.h"
#include "Platform.h"
int main()
{
    RenderWindow window(VideoMode({600,800}), "Game");
    window.setFramerateLimit(165);

    Player player;
    Platform platform;
    Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
            else if (const auto& keyPressed = event->getIf<Event::KeyPressed>())
            {
                if (keyPressed->scancode == Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
        }

        player.Move(deltaTime);

        window.clear();

        player.Draw(window);
        platform.Draw(window);
        window.display();
    }
}