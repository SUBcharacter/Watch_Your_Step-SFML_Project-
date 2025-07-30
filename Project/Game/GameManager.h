#pragma once
#include "IntegrationLibrary.h"
#include "Collider.h"
#include "Grid.h"
#include <fstream>
#include <sstream>
#include "data/include/nlohmann/json.hpp"

using json = nlohmann::json;

class GameManager
{
private:
	Player& player;
	vector<Platform*> allPlatform;
	Grid grid;
	Collider& collider;
	Texture texture;
	Texture texturewall;
	Texture texturewall2;
	Sprite sprite;
	Sprite Leftwall;
	Sprite Rightwall;


public:
	GameManager(const string& filepath, const string& LeftwallPath, const string& RightwallPath, Player& player, Collider& collider, Grid& grid);
	~GameManager();
	void LoadPlatformsFromJSON(const std::string& filepath);
	void Init();
	void Update(float deltaTime);
	void Draw(RenderWindow& window);
	PlatformType StringtoPlatformType(const string& typestring);
	JumpForceLevel StringtoJumpForceLevel(const string& Levelstring);
	vector<Platform*>& Getallplatform();
	float GetJumpForce(JumpForceLevel level);
};

