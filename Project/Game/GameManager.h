#pragma once
#include "IntegrationLibrary.h"
#include "Collider.h"
#include "Grid.h"
#include <fstream>
#include <sstream>

class GameManager
{
private:
	Player player;
	vector<Platform*> allPlatform;
	Grid grid;
	Collider collider;
	Texture texture;

public:
	GameManager(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height , float jumpForce, float mr, float speed, int dir);
	vector<GameManager*> LoadPlatformsFromTXT(const std::string& filepath, Player& player);
	void Init();
	void Update(PlatformType type,float deltaTime);
	void Draw(RenderWindow& window);
	PlatformType StringtoPlatformType(const std::string& typestring);
};

