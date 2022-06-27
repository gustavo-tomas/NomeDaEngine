#include "../header/Vec2.h"

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2 Vec2::operator + (Vec2 const &obj)
{
    Vec2 res;
    res.x = x + obj.x;
    res.y = y + obj.y;
    return res;
}

Vec2 Vec2::operator - (Vec2 const &obj)
{
    Vec2 res;
    res.x = x - obj.x;
    res.y = y - obj.y;
    return res;
}

Vec2 Vec2::Sub2(Vec2 v)
{
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::Mult2(float e)
{
    return Vec2(x * e, y * e);
}

Vec2 Vec2::GetRotated(float angle)
{
    float x2 = x * cos(angle) - y * sin(angle);
    float y2 = y * cos(angle) + x * sin(angle);
    return Vec2(x2, y2);
}