#include "IntegrationLibrary.h"
#include "GameManager.h"
int main()
{
	RenderWindow window(VideoMode({ 600, 800 }), "Test");
	window.setFramerateLimit(100);

	Clock clock;

	Player player("Assets/player.png", { 100,400 }, 0, 0, 50, 50);
	vector<Platform*> platform;
	platform.push_back(new Platform("Assets/player.png", STATIC, { 100,500 }, 0, 0, 200, 50));
	platform.push_back(new MovingPlatform("Assets/player.png", MOVING, { 300, 600 }, 0, 0, 50, 50,600,100,1));
	platform.push_back(new JumpPlatform("Assets/player.png", JUMP, { 500,500 }, 0, 0, 200, 50, 500.f));
	platform.push_back(new JumpPlatform("Assets/player.png", JUMP, { 0,800 }, 0, 0, 800, 50, 2000.f));
	Grid grid(100);
	Collider collider(player);

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

		collider.Collider2D(grid.nearByPlayerPlatform(player.GetnearGridcells()));

		player.Update(deltaTime);

		for (Platform* p : platform)
		{
			p->Draw(window);
		}
		player.Draw(window);

		window.display();
	}

	return 0;
}
