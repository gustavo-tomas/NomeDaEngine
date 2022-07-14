#include "../header/Collider.h"

#define DEBUG // @TODO: comment when in release mode

#ifdef DEBUG
#include "../header/Camera.h"
#include "../header/Game.h"
#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated)
{
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt)
{
    // :)
}

void Collider::Render() {

    // This section was moved from Update to better reflect changes in the hitbox
    box.SetVec(associated.box.GetCenter() + offset.GetRotated(associated.angleDeg));
    if (scale.x > 0)
    {
        box.w = associated.box.w * scale.x;
        box.x -= (associated.box.w * scale.x) / 2.0;
    }
    
    if (scale.y > 0)
    {
        box.h = associated.box.h * scale.y;
        box.y -= (associated.box.h * scale.y) / 2.0;
    }
    // Section ends here

    #ifdef DEBUG
        Vec2 center(box.GetCenter());
        SDL_Point points[5];

        Vec2 point = (Vec2(box.x, box.y) - center).GetRotated(associated.angleDeg) + center - Camera::pos;
        points[0] = { (int) point.x, (int) point.y };
        points[4] = { (int) point.x, (int) point.y };
        
        point = (Vec2(box.x + box.w, box.y) - center).GetRotated(associated.angleDeg) + center - Camera::pos;
        points[1] = { (int) point.x, (int) point.y };
        
        point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated(associated.angleDeg) + center - Camera::pos;
        points[2] = { (int) point.x, (int) point.y };
        
        point = (Vec2(box.x, box.y + box.h) - center).GetRotated( associated.angleDeg) + center - Camera::pos;
        points[3] = { (int) point.x, (int) point.y };

        SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
    #endif // DEBUG
}

bool Collider::Is(const char* type)
{
    string str_type = type;
    return str_type == "Collider";
}

void Collider::SetScale(Vec2 scale)
{
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset)
{
    this->offset = offset;
}