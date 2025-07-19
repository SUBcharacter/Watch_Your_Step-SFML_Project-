#include "GameManager.h"

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
