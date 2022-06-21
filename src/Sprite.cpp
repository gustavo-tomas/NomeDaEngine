#include "Sprite.h"

Sprite::Sprite()
{
    texture = nullptr;
}

Sprite::Sprite(const char* file)
{
    texture = nullptr;
    Open(file);
}

// @TODO: fix this
Sprite::Sprite(const char* file, SDL_Renderer* renderer)
{
    this->renderer = renderer;
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite()
{
    if (texture != nullptr)
        SDL_DestroyTexture(texture);
    cout << "Texture destroyed successfully!" << endl;
}

void Sprite::Open(const char* file)
{
    if (texture != nullptr)
        SDL_DestroyTexture(texture);

    if ((texture = IMG_LoadTexture(renderer, file)) == nullptr)
    {
        cout << "Error loading texture " << file << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "Texture " << file << " loaded successfully!" << endl;

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height); // @TODO: hardcoded x, y
    Render(0, 0);                 // @TODO: hardcoded x, y
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

    SDL_RenderCopy(renderer, texture, &clipRect, &dstRect);
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