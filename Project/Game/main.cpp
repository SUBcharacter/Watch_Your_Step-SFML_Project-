#include "IntegrationLibrary.h"
#include "GameManager.h"
#include "Camera.h"

int main()
{
	RenderWindow window(VideoMode({ 800,600 }), "Test");
	window.setFramerateLimit(100);

	Clock clock;

	Player player("Assets/player.png", { 1000,100 }, 0, 0, 40, 40);  // 플레이 영역 {x : 900 ~ 1700, y = 0 ~ 40000}
	vector<Platform*> platform;
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1025, 200 }, 0, 0, 250, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1480, 375 }, 0, 0, 300, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1000, 625 }, 0, 0, 200, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1220, 625 }, 370, 0, 60, 25,600.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1670, 525 }, 370, 0, 60, 25,600.f));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1200, 875 }, 0, 0, 200, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1025 ,1200 }, 0, 0, 250, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1005, 1050 }, 370, 0, 60, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1530, 1070 }, 260, 0, 280, 25, 1200.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1340, 1120 }, 370, 0, 60, 25, 1200.f));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1540 ,1300 }, 0, 0, 140, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1320 ,1500 }, 0, 0, 190, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1010 ,1590 }, 0, 0, 90, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1430, 1400 }, 370, 0, 60, 25, 1200.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1065, 1870 }, 370, 0, 60, 25, 1800.f));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1100 ,1990 }, 0, 0, 400, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1320 ,1940 }, 0, 0, 50, 25));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1450 , 1890 }, 0, 0, 50, 25,150,100.f,1));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1320 , 1840 }, 0, 0, 50, 25));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1450 , 1790 }, 0, 0, 50, 25, 120, 100.f, 1));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1450, 1990 }, 250, 0, 300, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1585, 1890 }, 365, 0, 70, 25, 1200.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1655, 1590 }, 370, 0, 60, 25, 1800.f));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1650, 2140 }, 0, 0, 100, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1625, 2190 }, 325, 0, 150, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1340, 2290 }, 370, 0, 60, 25, 600.f));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1535 , 2390 }, 0, 0, 50, 25, 200, 100.f, 1));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1080 , 2240 }, 0, 0, 50, 25, 200, 100.f, -1));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1590, 2640 }, 0, 0, 220, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1240, 2640 }, 160, 0, 480, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1030, 2390 }, 370, 0, 60, 25, 2400.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1030, 2515 }, 370, 0, 60, 25, 1200.f));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1410, 2590 }, 0, 0, 80, 20));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1310, 2530 }, 0, 0, 80, 20));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1210, 2470 }, 0, 0, 80, 20));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1310, 2410 }, 0, 0, 80, 20));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1210, 2350 }, 0, 0, 80, 20));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1410, 2350 }, 0, 0, 80, 20));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1050, 3440 }, 0, 0, 300, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1550, 3440 }, 0, 0, 300, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1110, 2760 }, 325, 0, 150, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1380, 2880 }, 325, 0, 150, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 975 , 3000 }, 325, 0, 150, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1560, 3100 }, 325, 0, 150, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1240, 3200 }, 325, 0, 150, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1110, 3310 }, 325, 0, 150, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1480, 3310 }, 325, 0, 150, 25, 1800.f));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1125 , 2830 }, 0, 0, 100, 20, 350, 100.f, 1));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1450 , 3000 }, 0, 0, 100, 20, 300, 100.f, -1));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1300 , 3355 }, 0, 0, 180, 20, 500, 120.f, 1));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 935 , 2760 }, 0, 0, 70 , 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1600, 3670 }, 0, 0, 200, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1025, 3760 }, 0, 0, 250, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1550, 3920 }, 0, 0, 300, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 930 , 4160 }, 0, 0, 60 , 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1540, 4220 }, 0, 0, 320, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1205, 3630 }, 365, 0, 70, 25, 1200.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1357, 3790 }, 365, 0, 70, 25, 600.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1153, 3990 }, 365, 0, 70, 25, 2400.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1370, 4065 }, 365, 0, 70, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1306, 4210 }, 365, 0, 70, 25, 3000.f));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1350, 4720 }, 0, 0, 700, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1252, 4450 }, 365, 0, 70, 25, 1800.f));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1100 , 4320 }, 0, 0, 100, 25, 300, 120.f, 1));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1500 , 4440 }, 0, 0, 100, 25, 300, 100.f, -1));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1100 , 4580 }, 0, 0, 100, 25, 300, 80.f, 1));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1050 , 4870 }, 0, 0, 300, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1343 , 4950 }, 0, 0, 75, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1551 , 5020 }, 0, 0, 75, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1200 , 5400 }, 0, 0, 600, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1170 , 5000 }, 350, 0, 100, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1054 , 5120 }, 350, 0, 100, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1433 , 5107 }, 350, 0, 100, 25, 1800.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1220 , 5257 }, 350, 0, 100, 25, 1800.f));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1380 , 5030 }, 0, 0, 60, 25, 200, 100.f, 1));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1350 , 5580 }, 0, 0, 700, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1650 , 5400 }, 350, 0, 100, 25, 2400.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1600 , 5560 }, 375, 0, 50, 25, 600.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1400 , 5560 }, 375, 0, 50, 25, 600.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1200 , 5560 }, 375, 0, 50, 25, 600.f));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1000 , 5560 }, 375, 0, 50, 25, 600.f));
	platform.push_back(new MovingPlatform("Assets/platform_static.png", MOVING, { 1550 , 5425 }, 0, 0, 100, 25, 200, 100.f, 1));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 950  , 5708 }, 0, 0, 100, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1150 , 5708 }, 0, 0, 100, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1350 , 5708 }, 0, 0, 100, 25));
	platform.push_back(new Platform("Assets/platform_static.png", STATIC, { 1550 , 5708 }, 0, 0, 100, 25));
	platform.push_back(new JumpPlatform("Assets/platform_jump.png", JUMP, { 1225 , 5775 }, 75 , 0, 700, 25, 1800.f));

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
		window.clear(Color::White);
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
