#include "TitleScreen.h"

TitleScreen::TitleScreen()
	: backGround(SpriteUse("Assets/Title/title.png", { 1201.0f, 802.0f }, { 1201.0f / 2.f, 802.0f / 2.f })),
	startGame(SpriteUse("Assets/Title/T_B_Start.png", { 350.f,75.f }, { 1201.0f / 2.f,  802.0f / 2.f })),
	exitGame(SpriteUse("Assets/Title/T_B_Exit.png", { 350.f,75.f }, { 1201.0f / 2.f,   (802.0f / 2.f) + 100.f })),
	pauseBack(SpriteUse("Assets/Pause/P_pause.png", { 1200.f, 800.f }, { 0.f,0.f })),
	continueGame(SpriteUse("Assets/Pause/P_B_Continue.png", { 350.0f, 75.f }, { 0.f,0.f })),
	breakGame(SpriteUse("Assets/Ending/E_B_Exit.png", { 350.0f, 75.f }, { 0.f,0.f })),
	clearBack(SpriteUse("Assets/Ending/ending.png", {1201.0f, 802.0f} , {0.f,0.f})),
	repeatGame(SpriteUse("Assets/Ending/E_B_Restart.png", { 350.0f, 75.0f }, { 0.f,0.f }))
{


}

void TitleScreen::Draw(RenderWindow& window)
{
	window.draw(backGround.spr);
	window.draw(startGame.spr);
	window.draw(exitGame.spr);
}

void TitleScreen::UpdateTitle(RenderWindow& window, Camera& camera)
{
	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	
	bool isPressed = Mouse::isButtonPressed(Mouse::Button::Left);

	bool justClicked = isPressed && !wasLastPressed;

		if (startGame.spr.getGlobalBounds().contains(mousePos))
		{
			startGame.spr.setColor(sf::Color(255, 255, 255, 255));
		if (justClicked)
			{
				startGame.spr.setColor(sf::Color(200, 200, 200, 150));

				state = GAMEPLAY;
				isPaused = false;
				camera.C_StartGame({ 1300,100 });
				
			}
		}
		else if (exitGame.spr.getGlobalBounds().contains(mousePos))
		{
			exitGame.spr.setColor(sf::Color(255, 255, 255, 255));
			if (justClicked)
			{
				exitGame.spr.setColor(sf::Color(200, 200, 200, 150));
				state = EXIT;
			}
		}
		else
		{
			startGame.spr.setColor(sf::Color(225, 225, 225, 255));
			exitGame.spr.setColor(sf::Color(225, 225, 225, 255));
		}
		wasLastPressed = isPressed;

		Draw(window);
	}

void TitleScreen::UpdatePaused(RenderWindow& window, Camera& camera)
{
	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

	pauseBack.spr.setPosition(camera.C_GetView().getCenter());
	continueGame.spr.setPosition({ camera.C_GetView().getCenter().x, camera.C_GetView().getCenter().y});
	breakGame.spr.setPosition({ camera.C_GetView().getCenter().x, camera.C_GetView().getCenter().y + 100.f });

	bool isPressed = Mouse::isButtonPressed(Mouse::Button::Left);

	bool justClicked = isPressed && !wasLastPressed;


		if (continueGame.spr.getGlobalBounds().contains(mousePos))
		{
			continueGame.spr.setColor(sf::Color(255, 255, 255, 255));
			if (justClicked)
			{
				continueGame.spr.setColor(sf::Color(200, 200, 200, 150));

				isPaused = false;

			}
		}
		else if (breakGame.spr.getGlobalBounds().contains(mousePos))
		{
			breakGame.spr.setColor(sf::Color(255, 255, 255, 255));
			if (justClicked)
			{
				breakGame.spr.setColor(sf::Color(200, 200, 200, 150));
				state = TITLE;
				camera.C_StartGame({ 600.f, 400.f });
			}
		}
		else
		{
			continueGame.spr.setColor(sf::Color(225, 225, 225, 255));
			breakGame.spr.setColor(sf::Color(225, 225, 225, 255));
		}

		wasLastPressed = isPressed;

		window.draw(pauseBack.spr);
		window.draw(continueGame.spr);
		window.draw(breakGame.spr);
	
}

void TitleScreen::UpdateClear(RenderWindow& window, Camera& camera)
{
	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	clearBack.spr.setPosition(camera.C_GetView().getCenter());
	repeatGame.spr.setPosition({ camera.C_GetView().getCenter().x, camera.C_GetView().getCenter().y });
	breakGame.spr.setPosition({ camera.C_GetView().getCenter().x, camera.C_GetView().getCenter().y + 100.f });

	bool isPressed = Mouse::isButtonPressed(Mouse::Button::Left);

	bool justClicked = isPressed && !wasLastPressed;

	if (repeatGame.spr.getGlobalBounds().contains(mousePos))
	{
		repeatGame.spr.setColor(sf::Color(255, 255, 255, 255));
		if (justClicked)
		{
			repeatGame.spr.setColor(sf::Color(200, 200, 200, 150));

			isPaused = false;
			state = GAMEPLAY;
			camera.C_StartGame({ 1300,100 });

		}
	}
	else if (breakGame.spr.getGlobalBounds().contains(mousePos))
	{
		breakGame.spr.setColor(sf::Color(255, 255, 255, 255));
		if (justClicked)
		{
			breakGame.spr.setColor(sf::Color(200, 200, 200, 150));
			state = TITLE;
			camera.C_StartGame({ 600.f, 400.f });
		}
	}
	else
	{
		continueGame.spr.setColor(sf::Color(225, 225, 225, 255));
		breakGame.spr.setColor(sf::Color(225, 225, 225, 255));
	}

	wasLastPressed = isPressed;

	window.draw(clearBack.spr);
	window.draw(repeatGame.spr);
	window.draw(breakGame.spr);


}

void TitleScreen::run()
{
	RenderWindow window(VideoMode({ 1200, 800 }), "Test");
	window.setFramerateLimit(100);

	Clock clock;

	Player player("Assets/PlayerSprite.png", { 1000,100 }, 0, 0, 35, 50);
	Grid grid;

	Collider collider(player);

	GameManager gamemanager("Assets/background_Center.png", "Assets/Wall.png", "Assets/Wall.png", player, collider, grid);

	gamemanager.LoadPlatformsFromJSON("PlatformJsondata/PlatformData.json");


	Camera camera({ 1200, 800 });
	camera.C_StartGame({ 600.f, 400.f });


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

		window.setView(camera.C_GetView());

		switch (state)
		{
		case TITLE:
			UpdateTitle(window, camera);
			break;
		case GAMEPLAY:
			if (!isPaused)
			{
				gamemanager.Update(deltaTime);

				if (gamemanager.GameClear())
				{
					state = CLEAR;
				}

				camera.C_UpdateView(player.GetPlayerPos());
			}
			gamemanager.Draw(window);

			if (isPaused)
			{
				UpdatePaused(window, camera);
			}

			break;
		case CLEAR:
			UpdateClear(window, camera);
			break;
		case EXIT:
			return;
			break;
		}



		window.display();
	}

}

