#include "../header/Sprite.h"
#include "../header/Game.h"

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
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        cout << "Texture destroyed successfully!" << endl;
    }
    else
        cout << "No texture to destroy!" << endl;
}

void Sprite::Open(const char* file)
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        cout << "Previous texture destroyed successfully!" << endl;
    }

    if ((texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file)) == nullptr)
    {
        cout << "Error loading texture " << file << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "Texture " << file << " loaded successfully!" << endl;

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);

    // @TODO: check if correct
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
    SDL_Rect dstRect;
    dstRect.x = associated.box.x;
    dstRect.y = associated.box.y;
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