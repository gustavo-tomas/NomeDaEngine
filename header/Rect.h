#ifndef RECT_H
#define RECT_H

#include <vector>

using namespace std;

class Rect {
    public:
        Rect(float x = 0, float y = 0, float w = 0, float h = 0);
        float x;
        float y;
        float w;
        float h;
        bool Contains(vector<float> point);
};


#endif // RECT_H