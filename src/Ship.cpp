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
    hp = 5;
    GameData::playerLives = hp;
    
    Sprite* sprite = new Sprite(associated, "./assets/image/ship.png", 6);
    sprite->SetScale(0.125, 0.125);
    associated.AddComponent(sprite);

    Sound* shipDamagedSound = new Sound(associated, "./assets/audio/damage.mp3");
    associated.AddComponent(shipDamagedSound);

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

    // Updates timers
    shootTimer.Update(dt);
    invincibleTimer.Update(dt);

    // Shoots
    if (InputManager::GetInstance().IsKeyDown(SPACE_KEY) && shootTimer.Get() >= 0.30)
        Shoot();

    float acc = 700.0;
    float dec = 50.0;
    float maxSpeed = 200.0;

    // Updates sprite
    Sprite* sprite = (Sprite *) associated.GetComponent("Sprite");

    // Forwards
    if (sprite != nullptr && InputManager::GetInstance().IsKeyDown(W_KEY))
        sprite->SetFrame(1);

    // Backwards
    else if (sprite != nullptr && InputManager::GetInstance().IsKeyDown(S_KEY))
        sprite->SetFrame(4);

    // Turns right
    else if (sprite != nullptr && InputManager::GetInstance().IsKeyDown(D_KEY))
        sprite->SetFrame(2);
    
    // Turns left
    else if (sprite != nullptr && InputManager::GetInstance().IsKeyDown(A_KEY))
        sprite->SetFrame(3);

    // Idle
    else if (sprite != nullptr)
        sprite->SetFrame(0);

    // Damaged
    if (sprite != nullptr && invincibleTimer.Get() <= 2.0)
        sprite->SetFrame(5);

    // Accelerates
    if (InputManager::GetInstance().IsKeyDown(W_KEY))
        linearSpeed = linearSpeed < maxSpeed ? linearSpeed + acc * dt : maxSpeed;

    // Decelerates
    if (InputManager::GetInstance().IsKeyDown(S_KEY))
        linearSpeed = linearSpeed > -maxSpeed ? linearSpeed - acc * dt : -maxSpeed;

    // Turns Right
    if (InputManager::GetInstance().IsKeyDown(D_KEY))
        angle += 4.5 * dt;

    // Turns Left
    if (InputManager::GetInstance().IsKeyDown(A_KEY))
        angle -= 4.5 * dt;

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
    Bullet* bullet = new Bullet(*bulletGo, angle - (M_PI / 4.0), speed, damage, maxDistance, "./assets/image/bullet.png", 1, 1.0, false);
    
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
    Asteroid* asteroid = (Asteroid*) other.GetComponent("Asteroid");
    if (asteroid != nullptr && invincibleTimer.Get() > 2.0)
    {
        Sprite* sprite = (Sprite *) associated.GetComponent("Sprite");
        if (sprite != nullptr) sprite->SetFrame(5);

        hp -= 1;
        GameData::playerLives = hp;
        
        // Damaged sfx
        Sound* shipDamagedSound = (Sound *) associated.GetComponent("Sound");
        if (shipDamagedSound != nullptr) shipDamagedSound->Play(1);

        if (hp <= 0)
        {
            Camera::Unfollow();

            GameObject* shipDeathGo = new GameObject();

            Sprite* shipDeathSprite = new Sprite(*shipDeathGo, "./assets/image/explosion.png", 4, 0.75, 3.0);
            shipDeathSprite->SetScale(0.35, 0.35);
            shipDeathGo->AddComponent(shipDeathSprite);
            shipDeathGo->box = associated.box;
            
            Sound* shipDeathSound = new Sound(*shipDeathGo, "./assets/audio/boom.wav");
            shipDeathSound->Play(1);
            shipDeathGo->AddComponent(shipDeathSound);

            Game::GetInstance().GetCurrentState().AddObject(shipDeathGo);
        }

        invincibleTimer.Restart();
    }
}