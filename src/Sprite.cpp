#include "../header/Sprite.h"
#include "../header/Game.h"
#include "../header/Resources.h"
#include "../header/Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated)
{
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, const char* file) : Sprite(associated)
{
    Open(file);
}

Sprite::~Sprite()
{
    
}

void Sprite::Open(const char* file)
{
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);

    associated.box.w = width;
    associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int width, int height)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = width;
    clipRect.h = height;
}

void Sprite::Update(float dt)
{

}

void Sprite::Render()
{
    Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

void Sprite::Render(int x, int y)
{
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    if (texture == nullptr || SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect) < 0)
    {
        cout << "Error rendering copy" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
}

bool Sprite::Is(const char* type)
{
    string str_type = type;
    return (str_type == "Sprite");
}

int Sprite::GetWidth()
{
    return width;
}

int Sprite::GetHeight()
{
    return height;
}

bool Sprite::IsOpen()
{
    if (texture != nullptr)
        return true;
    return false;
}