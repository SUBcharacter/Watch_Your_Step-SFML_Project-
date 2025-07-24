#include "GameManager.h"


GameManager::GameManager(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height , float jumpForce, float mr, float speed, int dir) : player(player), grid(100.f), collider(player)
{
}

GameManager::~GameManager()
{
	for (Platform* allplatform : allPlatform)
	{
		delete allplatform;
	}
	allPlatform.clear();
}

void GameManager::LoadPlatformsFromJSON(const std::string& filepath)
{

	allPlatform.reserve(104);

	ifstream file(filepath);
	if (!file.is_open())
	{
		cout << " File not found" << endl;
		return;
	}
	json Data;
	file >> Data;
	
	for (const auto& informa : Data)
	{
		string texturePath = informa["texturePath"];
		string typestr = informa["type"];
		string levelstr = informa["level"];
		PlatformType type = StringtoPlatformType(typestr);
		JumpForceLevel level = StringtoJumpForceLevel(levelstr);
		float x = informa["x"];
		float y = informa["y"];
		Vector2f pos = { x,y };
		int left = informa["left"];
		int top = informa["top"];
		int width = informa["width"];
		int height = informa["height"];

		switch (type)
		{
		case STATIC:
			allPlatform.push_back(new Platform(texturePath, type, pos, left, top, width, height));
			break;
		case JUMP:

			float jumpForce = GetJumpForce(level);
			switch (level)
			{
			case ONE:
				allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, jumpForce));
				break;
			case TWO:
				allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, jumpForce));
				break;
			case THREE:
				allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, jumpForce));
				break;
			case FOUR:
				allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, jumpForce));
				break;
			case FIVE:
				allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, jumpForce));
				break;
			default:
				break;
			}
		case MOVING:
			float mr = informa.value("moveRange", 0.0f);
			float speed = informa.value("moveSpeed", 0.0f);
			int dir = informa.value("direction", 0);
			allPlatform.push_back(new MovingPlatform(texturePath, type, pos, left, top, width, height, mr, speed, dir));
			break;
		default:
			break;
		}
	
	
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

PlatformType  GameManager::StringtoPlatformType(const string& typestring)
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

JumpForceLevel GameManager::StringtoJumpForceLevel(const string& Levelstring)
{
	if (Levelstring == "ONE")
	{
		return ONE;
	}
	else if (Levelstring == "TWO")
	{
		return TWO;
	}
	else if (Levelstring == "THREE")
	{
		return THREE;
	}
	else if (Levelstring == "FOUR")
	{
		return FOUR;
	}
	else if (Levelstring == "FIVE")
	{
		return FIVE;
	}
}

float GameManager::GetJumpForce(JumpForceLevel level)
{
	return (static_cast<float>(level) + 1.f) * 600.f;
}

