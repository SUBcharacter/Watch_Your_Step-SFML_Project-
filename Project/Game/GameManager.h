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
	Player player;
	vector<Platform*> allPlatform;
	Grid grid;
	Collider collider;
	Texture texture;

public:
	GameManager(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height , float jumpForce, float mr, float speed, int dir);
	void LoadPlatformsFromJSON(const std::string& filepath);
	void Init();
	void Update(PlatformType type,float deltaTime);
	void Draw(RenderWindow& window);
	PlatformType StringtoPlatformType(const string& typestring);
	JumpForceLevel StringtoJumpForceLevel(const string& Levelstring);
	float GetJumpForce(JumpForceLevel level);
};

