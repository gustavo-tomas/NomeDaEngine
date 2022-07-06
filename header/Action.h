#ifndef ACTION_H
#define ACTION_H

#include "Vec2.h"
#include "InputManager.h"

class Action {
    public:
        enum ActionType {
            MOVE = RIGHT_MOUSE_BUTTON,
            SHOOT = LEFT_MOUSE_BUTTON,
        };
        float x;
        float y;
        Action(ActionType type, float x, float y);
        ActionType type;
        Vec2 pos;
};

#endif // ACTION_H