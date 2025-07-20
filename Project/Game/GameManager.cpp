#include "GameManager.h"

GameManager::GameManager(const string& texturePath, PlatformType type, Vector2f pos, int left, int top, int width, int height , float jumpForce, float mr, float speed, int dir) : player(player), grid(100.f), collider(player)
{
	
	switch (type)
	{
	case STATIC :
		allPlatform.push_back(new Platform("das", type, pos, left, top, width, height));
		break;
	case JUMP :
		JumpForceLevel Lv;
		switch (Lv)
		{
		case ONE:
			allPlatform.push_back(new JumpPlatform(texturePath, type, pos,left,top,width,height,200));
			break;

		case TWO:
			allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, 400));
			break;

		case THREE:
			allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, 600));
			break;

		case FOUR:
			allPlatform.push_back(new JumpPlatform(texturePath, type, pos, left, top, width, height, 800));
			break;

		case FIVE:
			allPlatform.push_back(new JumpPlatform(texturePath,type, pos, left, top, width, height, 1000));
			break;
		default:
			break;
		}
	
		break;
	case MOVING: 
		allPlatform.push_back(new MovingPlatform(texturePath,type,pos, left, top, width, height,mr,speed,dir));
		break;
	default:
		break;
	}
}

vector<GameManager*> GameManager::LoadPlatformsFromTXT(const std::string& filepath, Player& player)
{
	vector<GameManager*> loadfile;
	ifstream file(filepath);
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string texturePath, typestr;
		float x, y;
		int left, top, width, height;
		float jumpForce = 0.0f, moveRange = 0.0f, moveSpeed = 0.0f;
		int direction = 0;

		ss >> texturePath >> typestr >> x >> y>> left >> top >> width >> height >> jumpForce >> moveRange >> moveSpeed >> direction;

		PlatformType type = StringtoPlatformType(typestr);

		GameManager* gm = new GameManager(
			texturePath, type,Vector2f(x, y),
			left, top, width, height,
			jumpForce, moveRange, moveSpeed, direction
		);

		loadfile.push_back(gm);
	}

	return loadfile;
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
			grid.UnregisterPlatform(MovePlatForm);
			MovePlatForm->Update(deltaTime);
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
	else if (typestring == "MOVING");
	{
		return MOVING;
	}
}
