#include "GameManager.h"

GameManager::GameManager(const string& filepath, const string& LeftwallPath, const string& RightwallPath, Player& player, Collider& collider,Grid & grid) : player(player) ,collider(collider), grid(grid), sprite(texture),Leftwall(texturewall),Rightwall(texturewall2)
{
	if (!texture.loadFromFile(filepath))
	{
		cout << "file not found" << endl;
		return;
	}
	 
	if (!texturewall.loadFromFile(LeftwallPath))
	{
		cout << "file not found" << endl;
		return;
	}

	if (!texturewall2.loadFromFile(RightwallPath))
	{
		cout << "file not found" << endl;
		return;
	}
	sprite.setTextureRect(IntRect({0,0},{1200,10000}));
	sprite.setPosition({ 900,-3000 });

	Leftwall.setTextureRect(IntRect({ 0, 0 }, { 200, 10000 })); 
	Leftwall.setPosition({ 700, -3000 });
	
	Rightwall.setTextureRect(IntRect({ 0, 0 }, { 200, 10000 }));
	Rightwall.setScale({-1.f, 1.f}); 
	Rightwall.setPosition({ 1900, -3000 });
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
		string typestr = informa["type"];
		PlatformType type = StringtoPlatformType(typestr);
		string level = informa["jumpforcelevel"];
		float x = informa["posX"];
		float y = informa["posY"];
		Vector2f pos = { x,y };
		int left = informa["left"];
		int top = informa["top"];
		int width = informa["width"];
		int height = informa["height"];
		int mr;
		float speed;
		int dir;
		switch (type)
		{
		case STATIC:
			allPlatform.push_back(new Platform("Assets/platform_static.png", type, pos, left, top, width, height));
			break;
		case JUMP:
			switch (StringtoJumpForceLevel(level))
			{
			case ONE:
				allPlatform.push_back(new JumpPlatform("Assets/platform_jump1.png", type, pos, left, top, width, height, 600.f));
				break;
			case TWO:
				allPlatform.push_back(new JumpPlatform("Assets/platform_jump2.png", type, pos, left, top, width, height, 1200.f));
				break;
			case THREE:
				allPlatform.push_back(new JumpPlatform("Assets/platform_jump3.png", type, pos, left, top, width, height, 1800.f));
				break;
			case FOUR:
				allPlatform.push_back(new JumpPlatform("Assets/platform_jump4.png", type, pos, left, top, width, height, 2400.f));
				break;
			case FIVE:
				allPlatform.push_back(new JumpPlatform("Assets/platform_jump5.png", type, pos, left, top, width, height, 3000.f));
				break;
			default:
				break;
			}
			break;
		case MOVING:
		{
			mr = informa["moverange"];
			speed = informa["speed"];
			dir = informa["dir"];
			allPlatform.push_back(new MovingPlatform("Assets/platform_static.png", type, pos, left, top, width, height, mr, speed, dir));
			break;
		}
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

void GameManager::Update(float deltaTime)
{
	for (Platform* p : allPlatform)
	{
		p->Update(deltaTime);
	}
	for (Platform* p : allPlatform)
	{
		grid.UnregisterPlatform(p);
		grid.RegisterPlatform(p);
	}
	player.Update(deltaTime);
	collider.Collider2D(grid.nearByPlayerPlatform(player.GetnearGridcells()));
}

void GameManager::Draw(RenderWindow& window)
{
	window.draw(sprite);

	player.Draw(window);
	for (Platform* p : allPlatform)
	{
		p->Draw(window);
	}
	window.draw(Leftwall);
	window.draw(Rightwall);

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

vector<Platform*>& GameManager::Getallplatform()
{
	return allPlatform;
}

float GameManager::GetJumpForce(JumpForceLevel level)
{
	return (static_cast<float>(level) + 1.f) * 600.f;
}

