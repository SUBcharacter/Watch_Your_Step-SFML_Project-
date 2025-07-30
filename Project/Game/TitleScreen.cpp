#include "TitleScreen.h"
#include <iostream>

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
	if (!clickBuffer.loadFromFile("Assets/ClickSound.wav"))
	{
		cerr << "에러 : ClickSound 찾을 수 없음 " << endl;
	}

	clickSound = new Sound(clickBuffer);
	clickSound->setVolume(40.f);

	titleMusic = new Music("Assets/Title.wav");
	playMusic = new Music("Assets/GamePlay.wav");
	clearMusic = new Music("Assets/Clear.wav");

	titleMusic->setVolume(50.f);
	playMusic->setVolume(50.f);
	clearMusic->setVolume(50.f);

	titleMusic->setLooping(true);
	playMusic->setLooping(true);
}

void TitleScreen::Draw(RenderWindow& window)
{
	window.draw(backGround.spr);
	window.draw(startGame.spr);
	window.draw(exitGame.spr);
}

void TitleScreen::UpdateTitle(RenderWindow& window, Camera& camera, Player& player)
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
			clickSound->play();

			state = GAMEPLAY;
			isPaused = false;
			player.SetPlayerPos(playerStart);
			camera.C_StartGame({ 1300,100 });
			titleMusic->stop();
			playMusic->play();
		}
	}
	else if (exitGame.spr.getGlobalBounds().contains(mousePos))
	{
		exitGame.spr.setColor(sf::Color(255, 255, 255, 255));
		if (justClicked)
		{
			exitGame.spr.setColor(sf::Color(200, 200, 200, 150));
			clickSound->play();
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
	playMusic->setVolume(10.f);
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
			clickSound->play();
			isPaused = false;
			playMusic->setVolume(50.f);
		}
	}
	else if (breakGame.spr.getGlobalBounds().contains(mousePos))
	{
		breakGame.spr.setColor(sf::Color(255, 255, 255, 255));
		if (justClicked)
		{
			playMusic->stop();
			breakGame.spr.setColor(sf::Color(200, 200, 200, 150));
			clickSound->play();
			state = TITLE;
			camera.C_StartGame({ 600.f, 400.f });
			titleMusic->play();
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

void TitleScreen::UpdateClear(RenderWindow& window, Camera& camera, Player& player)
{
	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	clearBack.spr.setPosition(camera.C_GetView().getCenter());
	repeatGame.spr.setPosition({ camera.C_GetView().getCenter().x, camera.C_GetView().getCenter().y + 50 });
	breakGame.spr.setPosition({ camera.C_GetView().getCenter().x, camera.C_GetView().getCenter().y + 150.f });

	bool isPressed = Mouse::isButtonPressed(Mouse::Button::Left);

	bool justClicked = isPressed && !wasLastPressed;

	if (repeatGame.spr.getGlobalBounds().contains(mousePos))
	{
		repeatGame.spr.setColor(sf::Color(255, 255, 255, 255));
		if (justClicked)
		{
			repeatGame.spr.setColor(sf::Color(200, 200, 200, 150));
			clickSound->play();
			isPaused = false;
			state = GAMEPLAY;
			player.SetPlayerPos(playerStart);
			camera.C_StartGame({ 1300,100 });
			playMusic->play();
		}
	}
	else if (breakGame.spr.getGlobalBounds().contains(mousePos))
	{
		breakGame.spr.setColor(sf::Color(255, 255, 255, 255));
		if (justClicked)
		{
			breakGame.spr.setColor(sf::Color(200, 200, 200, 150));
			clickSound->play();
			state = TITLE;
			camera.C_StartGame({ 600.f, 400.f });
			titleMusic->play();
		}
	}
	else
	{
		repeatGame.spr.setColor(sf::Color(225, 225, 225, 255));
		breakGame.spr.setColor(sf::Color(225, 225, 225, 255));
	}

	wasLastPressed = isPressed;

	window.draw(clearBack.spr);
	window.draw(repeatGame.spr);
	window.draw(breakGame.spr);
}

TitleScreen::~TitleScreen()
{
	delete clickSound;
	delete titleMusic;
	delete playMusic;
	delete clearMusic;
}

void TitleScreen::run()
{
	RenderWindow window(VideoMode({ 1200, 800 }), "Test");
	window.setFramerateLimit(100);

	Clock clock;
	Vector2f playerStart = { 1350, 6500 };
	Player player("Assets/PlayerSprite.png", playerStart, 0, 0, 35, 40);
	Grid grid;

	Collider collider(player);

	GameManager gamemanager("Assets/background_Center.png", "Assets/Wall.png", "Assets/Wall.png", player, collider, grid);

	gamemanager.LoadPlatformsFromJSON("PlatformJsondata/PlatformData.json");


	Camera camera({ 1200, 800 });
	camera.C_StartGame({ 600.f, 400.f });
	titleMusic->play();

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
				playMusic->setVolume(50.f);
			}
		}
		}
		window.clear();

		window.setView(camera.C_GetView());

		switch (state)
		{
		case TITLE:
			UpdateTitle(window, camera, player);
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
			if (!clearMusicPlayed)
			{
				playMusic->stop();
				clearMusic->play();
				clearMusicPlayed = true;
			}
			UpdateClear(window, camera, player);
			break;
		case EXIT:
			return;
			break;
		}
		window.display();
	}
}
