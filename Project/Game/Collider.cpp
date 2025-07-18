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
