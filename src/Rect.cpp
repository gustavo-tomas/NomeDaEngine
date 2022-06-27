#include "../header/Rect.h"

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

bool Rect::Contains(vector<float> point)
{
    float pointX = point[0];
    float pointY = point[1];
    
    if (pointX >= x && pointX <= x + w)
        if (pointY >= y && pointY <= y + h)
            return true;
    
    return false;
}