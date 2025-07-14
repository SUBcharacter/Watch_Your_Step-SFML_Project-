#pragma once
#include "IntegrationLibrary.h"
#include <vector>
#include <utility>
#include "Platform.h"
#include <unordered_map>

class girdmap
{
private:
	float cellsize = 100.f;
	unordered_map<pair<int, int>, vector<Platform*>> cellmap;

public:
	void Addplatform(Platform* platform);
	

};

