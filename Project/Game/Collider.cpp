#include "Collider.h"

bool Collider::isColliding(const FloatRect& player, const FloatRect& platform)
{
    return player.findIntersection(platform).has_value();
}

CollideDir Collider::CollidingDirection(const FloatRect& player, const FloatRect& platform)
{
    FloatRect intersect = player.findIntersection(platform).value();

    if (intersect.size.x < intersect.size.y)
    {
        if (player.position.x < platform.position.x)
        {
            return LEFT_SIDE;
        }
        else
            return RIGHT_SIDE;
    }
    else
    {
        if (player.position.y < platform.position.y)
        {
            return TOP;
        }
        else
        {
            return UNDER;
        }
    }
}

void Collider::Collider2D(vector<Platform*> nearPlatform)
{

    player.IsOnGround = false;
    for (Platform* p : nearPlatform)
    {
        if (!p)
            continue;

        if (player.CrowdControl && p->GetType() != JUMP)
            continue;

        FloatRect playerHB = player.GetHitBox();
        FloatRect platformHB = p->GetHitBox();

        if (isColliding(playerHB, platformHB))
        {

            p->OnCollide(player, CollidingDirection(playerHB, platformHB));
        }
    }
}
