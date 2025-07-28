#include "IntegrationLibrary.h"
#include "GameManager.h"
#include "Camera.h"

int main()
{
	RenderWindow window(VideoMode({ 1200, 700 }), "Test");
	window.setFramerateLimit(100);

	Clock clock;

	Player player("Assets/player.png", { 1000,100 }, 0, 0, 40, 40);  // 플레이 영역 {x : 900 ~ 1700, y = 0 ~ 40000}


	Grid grid(100);
	Collider collider(player);
	Camera camera({ 1200,700 });

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
		}
		window.clear();
		for (Platform* p : gamemanager.Getallplatform())
		{
			p->Update(deltaTime);
		}
		
		for (Platform* p : gamemanager.Getallplatform())
		{
			grid.UnregisterPlatform(p);
			grid.RegisterPlatform(p);
		}

		player.Update(deltaTime);

		collider.Collider2D(grid.nearByPlayerPlatform(player.GetnearGridcells()));

		camera.C_UpdateView(player.GetPlayerPos());

		window.setView(camera.C_GetView());

		gamemanager.Draw(window);
		//for (Platform* p : gamemanager.Getallplatform())
		//{
		//	p->Draw(window);
		//}
		//
		//
		//player.Draw(window);

		window.display();
	}

	return 0;
}
