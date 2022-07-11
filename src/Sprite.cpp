#include "../header/Sprite.h"
#include "../header/Game.h"
#include "../header/Resources.h"
#include "../header/Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated)
{
    texture = nullptr;
    scale = Vec2(1, 1);
}

Sprite::Sprite(GameObject& associated, const char* file, int frameCount, float frameTime) : Sprite(associated)
{
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    timeElapsed = 0;
    currentFrame = 0;
    Open(file);
}

Sprite::~Sprite()
{
    
}

void Sprite::Open(const char* file)
{
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width / frameCount, height);

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
    timeElapsed += dt;
    if (timeElapsed > frameTime)
    {
        currentFrame = (currentFrame + 1) % frameCount;
        int frameWidth = width / frameCount;
        SetClip(frameWidth * currentFrame, 0, frameWidth, height);
        timeElapsed = 0;
    }
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
    dstRect.w = clipRect.w * scale.x;
    dstRect.h = clipRect.h * scale.y;

    if (SDL_RenderCopyEx(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstRect,
        associated.angleDeg, // 0° to 360° clockwise
        nullptr,
        SDL_FLIP_NONE) < 0)
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
    return (width / frameCount) * scale.x;
}

int Sprite::GetHeight()
{
    return height * scale.y;
}

void Sprite::SetScale(float scaleX, float scaleY)
{
    if (scaleX != 0)
    {
        scale.x = scaleX;
        float diff = abs(associated.box.w - abs(scaleX * associated.box.w));
        if (scaleX > 0)
            associated.box.x -= diff / 2.0;
        else
            associated.box.x += diff / 2.0;
    }

    if (scaleY != 0)
    {
        scale.y = scaleY;
        float diff = abs(associated.box.h - abs(scaleY * associated.box.h));
        if (scaleY > 0)
            associated.box.y -= diff / 2.0;
        else
            associated.box.y += diff / 2.0;
    }
}

Vec2 Sprite::GetScale()
{
    return scale;
}

void Sprite::SetFrame(int frame)
{
    currentFrame = frame;
    int frameWidth = width / frameCount;
    SetClip(frameWidth * currentFrame, 0, frameWidth, height);
}

void Sprite::SetFrameCount(int frameCount)
{
    // @TODO: wut
    this->frameCount = frameCount;
    this->currentFrame = 0;
}

void Sprite::SetFrameTime(float frameTime)
{
    this->frameTime = frameTime;
}

bool Sprite::IsOpen()
{
    if (texture != nullptr)
        return true;
    return false;
}