#pragma once
class Physics
{
private:
	int playerx = 100;
	int playery = 200; 
	int playerw = 50;
	int playerh = 50;

	int platfomx = 100;
	int platformy = 300;
	int platformw = 200;
	int platformh = 20;

	int h = 0;

	bool fall = false;
	float t;
	const float G = 9.81f;
	const float Vo = 11.f;
public:
	void Jump();
	void Collision();
};

