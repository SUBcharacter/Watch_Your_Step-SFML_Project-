#include "IntegrationLibrary.h"
#include "GameManager.h"
#include "Camera.h"
#include "TitleScreen.h"

int main()
{
	RenderWindow window(VideoMode({ 1200,800 }), "Test");
	window.setFramerateLimit(100);
	
	Clock clock;

	Player player("Assets/PlayerSprite.png", { 1000,0 }, 0, 0, 35, 50);  // �÷��� ���� {x : 900 ~ 1700, y = 0 ~ 40000}

	Grid grid;
	Collider collider(player);

	Camera camera({ 1200, 800 });

	bool isPaused = false;

	GameManager gamemanager("Assets/background_Center.png", "Assets/Wall.png", "Assets/Wall.png",player,collider,grid );
	gamemanager.LoadPlatformsFromJSON("PlatformJsondata/PlatformData.json");
	camera.C_StartGame({1300,100});
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}

			if (const auto keyPressed = event->getIf<Event::KeyPressed>())
			{
				if (keyPressed->scancode == Keyboard::Scancode::Escape)
				{
					isPaused = !isPaused;
				}
			}
		}

		window.clear();

		if (!isPaused)
		{
			gamemanager.Update(deltaTime);

			camera.C_UpdateView(player.GetPlayerPos());
		}
		
		window.setView(camera.C_GetView());


		gamemanager.Draw(window);
		
		if (isPaused)
		{
			
		}
		window.display();
	}
	
	return 0;
}
