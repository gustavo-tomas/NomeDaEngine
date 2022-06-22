#include "Vec2.h"

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2 Vec2::Sum2(Vec2 v)
{
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::Sub2(Vec2 v)
{
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::Mult2(float e)
{
    return Vec2(x * e, y * e);
}