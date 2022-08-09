#include "../header/Asteroid.h"
#include "../header/Sprite.h"
#include "../header/InputManager.h"
#include "../header/Camera.h"
#include "../header/Game.h"
#include "../header/Collider.h"
#include "../header/Bullet.h"
#include "../header/Sound.h"
#include "../header/Ship.h"
#include "../header/GameData.h"

int Asteroid::asteroidCount = 0;

Asteroid::Asteroid(GameObject& associated, float timeOffset) : Component(associated)
{
    Sprite* sprite = new Sprite(associated, "./assets/image/asteroid.png");
    associated.AddComponent(sprite);
    
    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    speed = Vec2(0, 0);
    hp = 20;
    asteroidCount++;
    state = AsteroidState::RESTING;
    this->timeOffset = timeOffset;
}

void Asteroid::Start()
{

}

Asteroid::~Asteroid()
{
    asteroidCount--;
}

void Asteroid::NotifyCollision(GameObject& other)
{
    Bullet* bullet = (Bullet*) other.GetComponent("Bullet");
    if (hp > 0 && bullet != nullptr && !bullet->targetsPlayer)
    {
        hp -= bullet->GetDamage();
        if (hp <= 0)
        {
            GameObject* asteroidDeathGo = new GameObject();
            asteroidDeathGo->box = associated.box;

            Sprite* asteroidDeathSprite = new Sprite(*asteroidDeathGo, "./assets/image/aliendeath.png", 4, 0.25, 1.0);
            asteroidDeathGo->AddComponent(asteroidDeathSprite);
            
            Sound* asteroidDeathSound = new Sound(*asteroidDeathGo, "./assets/audio/boom.wav");
            asteroidDeathSound->Play();
            asteroidDeathGo->AddComponent(asteroidDeathSound);

            Game::GetInstance().GetCurrentState().AddObject(asteroidDeathGo);
        }
    }
}

void Asteroid::Update(float dt)
{
    if (hp <= 0)
    {
        associated.RequestDelete();
        return;
    }
    
    associated.angleDeg -= (M_PI / 10.0) * dt; // @TODO: random rotation & speed

    // Resting State
    if (state == AsteroidState::RESTING)
    {
        restTimer.Update(dt);
        if (restTimer.Get() >= 1.5 + timeOffset)
        {
            if (Ship::player == nullptr)
                return;
            
            destination = Camera::pos + Vec2(GameData::WIDTH / 2.0, GameData::HEIGHT / 2.0); // Big brain time
            Vec2 asteroidPos = associated.box.GetCenter();
            float angle = asteroidPos.GetAngle(destination) - (M_PI / 4.0);
            speed = Vec2(100, 100).GetRotated(angle);
            state = AsteroidState::MOVING;
        }
    }

    // Moving State
    else
    {
        // Moving to destination
        if (distanceLeft <= 0)
            associated.RequestDelete(); 
        else
        {
            Vec2 deltaS = (speed * dt);
            associated.box.SetVec(associated.box.GetVec() + deltaS);
            distanceLeft -= deltaS.GetMagnitude();
        }
    }
}

void Asteroid::Render()
{

}

bool Asteroid::Is(const char* type)
{
    string str_type = type;
    return str_type == "Asteroid";
}