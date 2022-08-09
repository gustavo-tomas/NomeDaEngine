#include "../header/Ship.h"
#include "../header/Sprite.h"
#include "../header/Game.h"
#include "../header/InputManager.h"
#include "../header/Collider.h"
#include "../header/Bullet.h"
#include "../header/Camera.h"
#include "../header/Sound.h"
#include "../header/Collision.h"
#include "../header/GameData.h"
#include "../header/Asteroid.h"

Ship* Ship::player;

Ship::Ship(GameObject& associated) : Component(associated)
{
    speed = Vec2(0, 0);
    linearSpeed = 0;
    angle = 0;
    hp = 100;
    
    Sprite* sprite = new Sprite(associated, "./assets/image/ship.png");
    associated.AddComponent(sprite);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    player = this;
}

Ship::~Ship()
{
    player = nullptr;
}

void Ship::Start()
{
    
}

void Ship::Update(float dt)
{
    if (hp <= 0)
    {
        associated.RequestDelete();
        return;
    }

    // Shoots
    shootTimer.Update(dt);
    if (InputManager::GetInstance().IsKeyDown(SPACE_KEY) && shootTimer.Get() >= 0.40)
        Shoot();

    float acc = 700.0;
    float dec = 700.0;
    float maxSpeed = 200.0;

    // Accelerates
    if (InputManager::GetInstance().IsKeyDown(W_KEY))
        linearSpeed = linearSpeed < maxSpeed ? linearSpeed + acc * dt : maxSpeed;

    // Decelerates
    if (InputManager::GetInstance().IsKeyDown(S_KEY))
        linearSpeed = linearSpeed > -maxSpeed ? linearSpeed - acc * dt : -maxSpeed;

    // Turns Right
    if (InputManager::GetInstance().IsKeyDown(D_KEY))
        angle += 2.5 * dt;

    // Turns Left
    if (InputManager::GetInstance().IsKeyDown(A_KEY))
        angle -= 2.5 * dt;

    // Comes to a halt
    if (!InputManager::GetInstance().IsKeyDown(W_KEY) &&
        !InputManager::GetInstance().IsKeyDown(S_KEY))
    {
        linearSpeed = linearSpeed > 0 ? linearSpeed - dec * dt : linearSpeed;
        linearSpeed = linearSpeed < 0 ? linearSpeed + dec * dt : linearSpeed;
        linearSpeed = abs(linearSpeed) <= 5.0 ? 0 : linearSpeed - 1.0;
    }

    // Updates sprite and position
    associated.angleDeg = angle;
    speed = Vec2(linearSpeed, 0).GetRotated(angle);
    associated.box.SetVec(associated.box.GetVec() + speed * dt);
    
    // Limits X & Y position to the limits of the tilemap
    associated.box.x = min(1408.f - associated.box.w, associated.box.x);
    associated.box.x = max(0.f, associated.box.x);
    associated.box.y = min(1280.f - associated.box.h, associated.box.y);
    associated.box.y = max(0.f, associated.box.y);
}

void Ship::Shoot()
{
    float speed = 700;
    float damage = 10;
    float maxDistance = 1000;

    GameObject* bulletGo = new GameObject();
    Bullet* bullet = new Bullet(*bulletGo, angle - (M_PI / 4.0), speed, damage, maxDistance, "./assets/image/penguinbullet.png", 4, 0.5, false);
    
    Vec2 center = associated.box.GetCenter();
    Vec2 offset = Vec2(bulletGo->box.w / 2.0, bulletGo->box.h / 2.0) - Vec2(associated.box.w / 2.0, 0).GetRotated(angle);
    
    bulletGo->box.SetVec(center - offset);
    bulletGo->AddComponent(bullet);

    Game::GetInstance().GetCurrentState().AddObject(bulletGo);

    shootTimer.Restart();
}

void Ship::Render()
{

}

bool Ship::Is(const char* type)
{
    string str_type = type;
    return str_type == "Ship";
}

void Ship::NotifyCollision(GameObject& other)
{
    Asteroid* bullet = (Asteroid*) other.GetComponent("Asteroid");
    if (bullet != nullptr)
    {
        hp -= 10;
        if (hp <= 0)
        {
            Camera::Unfollow();

            GameObject* penguinDeathGo = new GameObject();
            penguinDeathGo->box = associated.box;

            Sprite* penguinDeathSprite = new Sprite(*penguinDeathGo, "./assets/image/penguindeath.png", 5, 0.25, 1.25);
            penguinDeathGo->AddComponent(penguinDeathSprite);
            
            Sound* penguinDeathSound = new Sound(*penguinDeathGo, "./assets/audio/boom.wav");
            penguinDeathSound->Play();
            penguinDeathGo->AddComponent(penguinDeathSound);

            Game::GetInstance().GetCurrentState().AddObject(penguinDeathGo);
        }
        cout << "PENGUIN HP: " << hp << endl;
    }
}