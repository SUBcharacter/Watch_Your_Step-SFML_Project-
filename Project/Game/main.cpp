#include "IntegrationLibrary.h"
#include "GameManager.h"
#include "Camera.h"

int main()
{
	RenderWindow window(VideoMode({ 1200,900 }), "Test");
	window.setFramerateLimit(100);

	Clock clock;

	Player player("Assets/player.png", { 1000,100 }, 0, 0, 40, 40);  // 플레이 영역 {x : 900 ~ 1700, y = 0 ~ 40000}
	vector<Platform*> platform;

	Grid grid;
	Collider collider(player);
	Camera camera({ 1200, 900 });

	bool isPaused = false;

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

		window.clear(Color::White);

		if (!isPaused)
		{
			for (Platform* p : platform)
			{
				p->Update(deltaTime);
			}

			for (Platform* p : platform)
			{
				grid.UnregisterPlatform(p);
				grid.RegisterPlatform(p);
			}

			player.Update(deltaTime);

			collider.Collider2D(grid.nearByPlayerPlatform(player.GetnearGridcells()));

			camera.C_UpdateView(player.GetPlayerPos());
		}
		

		window.setView(camera.C_GetView());

		for (Platform* p : platform)
		{
			p->Draw(window);
		}
		
		player.Draw(window);
		
		if (isPaused)
		{
			// 일시 정지 UI
			
		}

		window.display();
	}

	return 0;
}
