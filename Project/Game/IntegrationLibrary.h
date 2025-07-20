
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <vector>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>
#include <Windows.h>
#include <unordered_map>
#include <utility>

using namespace std;
using namespace sf;

enum CollideDir
{
	TOP,
	LEFT_SIDE,
	RIGHT_SIDE,
	UNDER
};

enum PlatformType
{
	STATIC,
	JUMP,
	MOVING
};

enum JumpForceLevel
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE
};