#include "GridManager.h"

int GridManager::Poskey(Vector2f pos)
{
	int x = static_cast<int>(pos.x) / cellsize;
	int y = static_cast<int>(pos.y) / cellsize;
	return x + y * gridwidth;
}

void GridManager::Addplatform(Platform& platform)
{
	Pos p = platform.GetPlatformPos();
	int key = Poskey(Vector2f(p.x,p.y));
	gridmap[key].push_back(platform);
}

vector<Platform> GridManager::Collidableplatform(Vector2f pos)
{
	vector<Platform> nearplatform;

	int px = static_cast<int>(pos.x) / cellsize;
	int py = static_cast<int>(pos.y) / cellsize;

	//픽셀 9개로 나누고 근처에 있는 발판 저장하기
	//다시 작업
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int x = px + dx;
                int y = py + dy;
                int key = x + y * gridwidth;
                auto it = gridmap.find(key);
                if (it != gridmap.end()) {
					nearplatform.insert(nearplatform.end(), it->second.begin(), it->second.end());
                }
            }
        }
   
	return nearplatform;
}


