#include "../header/Minion.h"
#include "../header/Sprite.h"
#include "../header/Bullet.h"
#include "../header/Game.h"
#include <string>

Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated)
{
    Sprite* sprite = new Sprite(associated, "./assets/image/minion.png");
    associated.AddComponent(sprite);
    
    float r = 1.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(1.5 - 1.0)));
    Vec2 scale = Vec2(r, r);
    sprite->SetScale(scale.x, scale.y);

    arc = arcOffsetDeg;
    this->alienCenter = alienCenter.lock().get();
}

void Minion::Update(float dt)
{
    if (alienCenter == nullptr)
    {
        associated.RequestDelete();
        return;
    }

    Vec2 rotated = Vec2(200, 0).GetRotated(arc);

    associated.angleDeg = arc * DEG; // Convert from Rad to Deg

    associated.box.x = alienCenter->box.x + associated.box.w / 2 + rotated.x;
    associated.box.y = alienCenter->box.y + associated.box.h / 2 + rotated.y;
    arc = arc <= 2.0 * M_PI ? arc + ANG_INC * dt : dt; // Prevent overflow of arc
}

void Minion::Shoot(Vec2 pos)
{
    // auto vTest = Vec2(512, 300); // @TODO: delete test
    // float angle = vTest.GetAngle(pos) - (M_PI / 4.0);
    float angle = associated.box.GetCenter().GetAngle(pos) - (M_PI / 4.0);
    float speed = 100;
    float damage = 10;
    float maxDistance = 1000;

    GameObject* bulletGo = new GameObject();
    Bullet* bullet = new Bullet(*bulletGo, angle, speed, damage, maxDistance, "./assets/image/minionbullet1.png");
    bulletGo->AddComponent(bullet);

    bulletGo->box.SetVec(associated.box.GetCenter());
    // bulletGo->box.SetVec(vTest);

    State& state = Game::GetInstance().GetState();
    state.AddObject(bulletGo);
}

void Minion::Render()
{

}

bool Minion::Is(const char* type)
{
    string str_type = type;
    return str_type == "Minion";
}