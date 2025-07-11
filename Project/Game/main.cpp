#include "IntegrationLibrary.h"
#include "Player.h"
int main()
{
    RenderWindow window(VideoMode({600,800}), "Game");
    window.setFramerateLimit(60);

    Player player;

    float groundY = 500.f;
    bool isOnGround = false;

    while (window.isOpen())
    {
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

        player.Move();

        window.clear();

        player.Draw(window);

        window.display();
    }
}