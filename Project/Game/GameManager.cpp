#include "GameManager.h"


GameManager::GameManager(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height , float jumpForce, float mr, float speed, int dir) : player(player), collider(player)
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

