#include "IntegrationLibrary.h"

int main()
{
    // ¿¹Á¦
    RenderWindow window(sf::VideoMode({ 800, 600 }), "Game");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}