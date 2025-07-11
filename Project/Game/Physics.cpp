#include "Physics.h"

void Physics::Jump()
{
	fall = true;
	t = 0.f;
	h = playery;
	if (fall)
	{
		t += 0.3f;
		playery = (int)(h - (Vo * t) + (0.5f * G * t * t));
		if (playery >= h)
		{
			playery = h;
			fall = false;
		}
	}

}

void Physics::Collision()
{
	playery = playery + 3;
}
