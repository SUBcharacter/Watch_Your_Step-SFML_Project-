#include "Title.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <vector>
#include <string>



Title::Title()
{


}

Title::~Title()
{
}

void Title::onEnter(Game_Manager& game)
{
	if (!m_backgroundTexture.loadFromFile("assets/cat1.png"))
	{
		std::cerr << "타이틀 배경로드 실패!";
		
	}
	else
	{
		//m_backgroundSprite.emplace(m_backgroundTexture); // 텍스처 로드 성공 시 스프라이트 초기화
		// 창 크기에 맞게 스케일 조정
		//m_backgroundSprite.setScale(
		//	static_cast<float>(game.getWindow().getSize().x) / m_backgroundTexture.getSize().x,
		//	static_cast<float>(game.getWindow().getSize().y) / m_backgroundTexture.getSize().y
		//);
		m_backgroundSprite.emplace(m_backgroundTexture);
		std::cout << "배경 이미지 로드 성공, has_value: " << m_backgroundSprite.has_value() << "\n";
		sf::Vector2f newS1(50.0f, 50.0f);
		m_backgroundSprite->setPosition(newS1);
	}

	if (!m_font.openFromFile("assets/KoPubDotumMedium.ttf"))
	{
		std::cerr << "폰트 출력 실패";
	}
	else
	{
	m_titleText.emplace(m_font);
	m_titleText->setString("game title");
	m_titleText->setCharacterSize(100);
	m_titleText->setFillColor(sf::Color::Black);
	//sf::Vector2f newP1(50.0f, 50.0f);
	//m_titleText->setPosition(newP1);


	m_pressEnterText.emplace(m_font);
	m_pressEnterText->setString("Enter");
	m_pressEnterText->setCharacterSize(50);
	m_pressEnterText->setFillColor(sf::Color::Yellow);
	//sf::Vector2f newP2(50.0f, 100.0f);
	//m_pressEnterText->setPosition(newP2);

	}
}




void Title::handleInput(Game_Manager& game, const sf::Event& event)
{
	if (event.is<sf::Event::KeyPressed>())
	{
		const auto* KeyPressed = event.getIf< sf::Event::KeyPressed>();
		if (KeyPressed)
		{
			if (KeyPressed->scancode==sf::Keyboard::Scancode::Enter)
			{
				//game 클래스에 상태 변환 요청
			}
		}

	}
	//추가 키 입력

}

void Title::update(Game_Manager& game, float deltaTime)
{



}

void Title::draw(Game_Manager& game, sf::RenderWindow& window)
{
	if (m_backgroundSprite.has_value())
	{
	window.draw(*m_backgroundSprite);
	}
	if (m_titleText.has_value())
	{
	window.draw(*m_titleText);
	}

	if (m_pressEnterText.has_value())
	{
	window.draw(*m_pressEnterText);
	}


}

void Title::onExit(Game_Manager& game)
{
}




