#include "GameManager.h"


GameManager::GameManager(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height , float jumpForce, float mr, float speed, int dir) : player(player), grid(100.f), collider(player)
{
}

void GameManager::LoadPlatformsFromJSON(const std::string& filepath)
{
	ifstream file(filepath);
	if (!file.is_open())
	{
		cout << " ������ �� �� �����ϴ� " << endl;
	}
	json Data;
	file >> Data;

	for (const auto& informa : Data)
	{
		//string texturePath = informa["texturePath"];
		//string typestr = informa["type"];
		//PlatformType type = StringtoPlatformType(typestr);
		//float x = informa["x"];
		//float y = informa["y"];
		//Vector2f pos = { x,y };
		//int left = informa["left"];
		//int top = informa["top"];
		//int width = informa["width"];
		//int height = informa["height"];
		//
		//switch (type)
		//{
		//case STATIC:
		//	allPlatform.push_back(new Platform(texturePath, type, pos, left, top, width, height));
		//	break;
		//case JUMP:
		//	float jumpForce = informa.value("jumpForce", 0.0f);
		//	if (jumpForce >= 600 && jumpForce < 1200)
		//	{
		//		allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, 600));
		//	}
		//	else if (jumpForce >= 1200 && jumpForce < 1800)
		//	{
		//		allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, 1200));
		//	}
		//	else if (jumpForce >= 1800 && jumpForce < 2400)
		//	{
		//		allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, 1800));
		//	}
		//	else if (jumpForce >= 2400 && jumpForce < 3000)
		//	{
		//		allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, 2400));
		//	}
		//	else if (jumpForce >= 3000)
		//	{
		//		allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, 3000));
		//	}
		//	break;
		//case MOVING:
		//	float mr = informa.value("moveRange", 0.0f);
		//	float speed = informa.value("moveSpeed", 0.0f);
		//	int dir = informa.value("direction", 0);
		//	allPlatform.push_back(new MovingPlatform(texturePath, type, pos, left, top, width, height, mr, speed, dir));
		//	break;
		//default:
		//	break;
		//}
	}
}


void GameManager::Init()
{
	for (Platform* p : allPlatform)
	{
		grid.RegisterPlatform(p);
	}

}

void GameManager::Update(PlatformType type, float deltaTime)
{
	for (Platform* p : allPlatform)
	{
		 
		MovingPlatform* MovePlatForm = dynamic_cast<MovingPlatform*>(p);
		if (MovePlatForm)
		{
			MovePlatForm->Update(deltaTime);
			grid.UnregisterPlatform(MovePlatForm);
			grid.RegisterPlatform(MovePlatForm);
		}
		else
		{
			p->Update(deltaTime);
		}
		player.Move(deltaTime);
		vector<pair<int, int>> Nearbycells = player.GetnearGridcells();
		vector<Platform*> NearbyPlatform = grid.nearByPlayerPlatform(Nearbycells);
		collider.Collider2D(NearbyPlatform);

	}
}

void GameManager::Draw(RenderWindow& window)
	{
	for (Platform* p : allPlatform)
	{
		p->Draw(window);
	}
	player.Draw(window);
	}

PlatformType  GameManager::StringtoPlatformType(const std::string& typestring)
{
	if (typestring == "STATIC")
	{
		return STATIC;
	}
	else if (typestring == "JUMP")
	{
		return JUMP;
	}
	else if (typestring == "MOVING")
	{
		return MOVING;
	}
}

