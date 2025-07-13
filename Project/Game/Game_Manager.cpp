#include "Game_Manager.h"
#include <string>



Game_Manager::Game_Manager() : m_window(sf::VideoMode(sf::Vector2u(600, 800)), "game"),
m_currentState(std::make_unique<Title>())
{
	m_window.setFramerateLimit(60);
	m_currentState = std::make_unique<Title>();
	m_currentState->onEnter(*this);
	std::cout << "start" << endl;
}

Game_Manager::~Game_Manager()
{
	cout << "end" << endl;
}

void Game_Manager::run()
{
	cout << "시작합니다." << endl;
	while (m_window.isOpen())
	{
		float deltaTime = m_clock.restart().asSeconds();//프래임간 시간 계산
		while (const std::optional<sf::Event>eventOpt = m_window.pollEvent())
		{
			const sf::Event& event = *eventOpt;

			if (event.is<sf::Event::Closed>())
			{
				m_window.close();
			}
			else if (const auto* keyPressed= event.getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode==sf::Keyboard::Scancode::Escape)
				{
					m_window.close();
				}
			}

			if (m_currentState)
			{
				m_currentState->handleInput(*this, event);
			}
						
		}
		if (m_currentState)
			{
				m_currentState->update(*this, deltaTime);
			}
			m_window.clear(sf::Color::Black);
			if (m_currentState)
			{
				m_currentState->draw(*this, m_window);
			}
	m_window.display();
	}
	std::cout << "Game: 메인 루프 종료.\n";
}


sf::RenderWindow& Game_Manager::getWindow()
{
	return m_window;
}
