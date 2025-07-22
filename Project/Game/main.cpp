#include "IntegrationLibrary.h"
#include "GameManager.h"
#include "Camera.h"

int main()
{
	RenderWindow window(VideoMode({ 800, 600 }), "Test");
	window.setFramerateLimit(100);

	Clock clock;

	Player player("Assets/player.png", { 1000,100 }, 0, 0, 50, 50);  // 플레이 영역 {x : 900 ~ 1700, y = 0 ~ 40000}
	vector<Platform*> platform;
	platform.push_back(new Platform("Assets/platform.png", STATIC, { 1000,200 }, 0, 0, 200, 40));
	platform.push_back(new Platform("Assets/platform.png", STATIC, { 1300,350 }, 0, 0, 200, 40));
	platform.push_back(new Platform("Assets/platform.png", STATIC, { 1000,500 }, 0, 0, 200, 40));
	platform.push_back(new MovingPlatform("Assets/platform.png", MOVING, {1300, 600 }, 0, 0, 50, 40,800,100,1));
	platform.push_back(new JumpPlatform("Assets/platform.png", JUMP, { 1000,800 }, 0, 0, 200, 40, 3000.f));
	platform.push_back(new Platform("Assets/platform.png", STATIC, { 1300,700 }, 0, 0, 200, 40));
	platform.push_back(new JumpPlatform("Assets/platform.png", JUMP, {1500,800 }, 0, 0, 200, 40, 600.f));
	platform.push_back(new JumpPlatform("Assets/platform.png", JUMP, {1300,10000 }, 0, 0, 800, 40, 3000.f));
	
	Grid grid(100);
	Collider collider(player);
	Camera camera({ 800,600 });

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

		window.setView(camera.C_GetView());

		for (Platform* p : platform)
		{
			p->Draw(window);
		}
		

		player.Draw(window);

		window.display();
	}

	return 0;
}
