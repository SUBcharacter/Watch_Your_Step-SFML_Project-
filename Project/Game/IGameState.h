#pragma once
#include "IntegrationLibrary.h"



class Game_Manager;


class IgameState
{
public:

	IgameState() = default;

	virtual ~IgameState() = default;

	virtual void onEnter(Game_Manager& game) = 0;
	virtual void handleInput(Game_Manager& game, const sf::Event& event)= 0;
	virtual void update(Game_Manager& game, float deltaTime) = 0;
	virtual void draw(Game_Manager& game, sf::RenderWindow& window) = 0;
	virtual void onExit(Game_Manager& game) = 0;



};

