#include "Collider.h"

bool Collider::isColliding(const FloatRect& player, const FloatRect& platform)
{
    return player.findIntersection(platform);
}
