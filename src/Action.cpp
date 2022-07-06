#include "../header/Action.h"

Action::Action(ActionType type, float x, float y)
{
    this->type = type; // @TODO: fix this type 
    this->x = x;
    this->y = y;
    this->pos = Vec2(x, y); // @TODO: dunno
}