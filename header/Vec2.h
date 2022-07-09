#ifndef VEC2_H
#define VEC2_H

#include <cmath>

class Vec2 {
    public:
        Vec2(float x = 0, float y = 0);
        Vec2 GetRotated(float angle);
        float GetAngle();
        float GetAngle(Vec2 terminal);
        float GetDistance(Vec2 vec);
        Vec2 operator + (Vec2 const &obj);
        Vec2 operator - (Vec2 const &obj);
        float x;
        float y;
};

#endif // VEC2_H