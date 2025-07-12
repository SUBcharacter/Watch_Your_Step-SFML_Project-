#include "Physics.h"

void Physics::Jump()
{

    //더 이상 떨어지지 않을 때 : 점프를 하지 않는 경우
    if (!fall) {
        Yspeed = -10.0f;
        fall = true;
    }

}

void Physics::Collision()
{
    Yspeed += gravity;
    playery += static_cast<int>(Yspeed);

    // 충돌 체크
    int playerBottom = playery + playerh;
    int platformTop = platformy;

    bool Xrange = (playerx + playerw > platformx) && (playerx < platformx + platformw);
    bool onPlatform = (playerBottom >= platformTop) && (playerBottom <= platformTop + platformh);

    if (Xrange && onPlatform && Yspeed >= 0) {
        playery = platformy - playerh;
        Yspeed = 0;
        fall = false;
    }
    else {
        fall = true;
    }
}
