#include "Sprite.h"
#include "Game.h"

Sprite::Sprite()
{
    texture = nullptr;
}

Sprite::Sprite(const char* file)
{
    texture = nullptr;
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
}

void Sprite::SetClip(int x, int y, int width, int height)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = width;
    clipRect.h = height;
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