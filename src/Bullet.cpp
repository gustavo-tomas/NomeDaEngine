#include "../header/Bullet.h"
#include "../header/Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed,
    int damage, float maxDistance, const char* sprite,
    int frameCount, float frameTime)
    : Component(associated)
{
    Sprite* bulletSprite = new Sprite(associated, sprite, frameCount, frameTime);
    bulletSprite->SetScale(1.2, 1.8);
    associated.AddComponent(bulletSprite);

    associated.angleDeg = (angle + (M_PI / 4.0)) * DEG;

    this->speed = Vec2(speed, speed).GetRotated(angle);
    this->damage = damage;
    this->distanceLeft = maxDistance;
}

void Bullet::Update(float dt)
{
    if (distanceLeft <= 0)
    {
        cout << "Bullet deleted" << endl;
        associated.RequestDelete();
        return;
    }
    
    float dX = speed.x * dt;
    float dY = speed.y * dt;

    associated.box.x += dX;
    associated.box.y += dY;
    distanceLeft -= sqrt(dX * dX + dY * dY);
}

void Bullet::Render()
{

}

bool Bullet::Is(const char* type)
{
    string str_type = type;
    return str_type == "Bullet";
}

int Bullet::GetDamage()
{
    return damage;
}