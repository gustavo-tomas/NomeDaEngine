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
const int Asteroid::maxAsteroidCount = 50;

Asteroid::Asteroid(GameObject& associated, float timeOffset, Vec2 scale, float rotation) : Component(associated)
{
    Sprite* sprite = new Sprite(associated, "./assets/image/asteroid.png");
    sprite->SetScale(scale.x, scale.y);
    associated.AddComponent(sprite);
    
    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    speed = Vec2(0, 0);
    hp = 10;
    asteroidCount++;
    state = AsteroidState::RESTING;
    this->scale = scale;
    this->timeOffset = timeOffset;
    this->rotation = rotation;
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

            Sprite* asteroidDeathSprite = new Sprite(*asteroidDeathGo, "./assets/image/explosion.png", 4, 0.25, 1.0);
            asteroidDeathSprite->SetScale(scale.x + 0.1, scale.y + 0.1);
            asteroidDeathGo->AddComponent(asteroidDeathSprite);
            asteroidDeathGo->box = associated.box;
            
            Sound* asteroidDeathSound = new Sound(*asteroidDeathGo, "./assets/audio/boom.wav");
            asteroidDeathSound->Play();
            asteroidDeathGo->AddComponent(asteroidDeathSound);

            Game::GetInstance().GetCurrentState().AddObject(asteroidDeathGo);
            GameData::score += 100;

            // Breaks asteroid in two parts
            if (scale.x >= 0.42)
            {
                for (int i = 0; i < 2; i++)
                {
                    GameObject* asteroidGo = new GameObject();
                    Asteroid* asteroid = new Asteroid(*asteroidGo, 0.0, scale / 2.0, rotation);

                    asteroidGo->box.SetVec(associated.box.GetCenter());

                    asteroidGo->AddComponent(asteroid);
                    Game::GetInstance().GetCurrentState().AddObject(asteroidGo);
                }
            }
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
    
    associated.angleDeg -= rotation * dt;

    // Resting State
    if (state == AsteroidState::RESTING)
    {
        restTimer.Update(dt);
        if (restTimer.Get() >= timeOffset)
        {
            if (Ship::player == nullptr)
                return;
            
            destination = Camera::pos + Vec2(GameData::WIDTH / 2.0, GameData::HEIGHT / 2.0); // Big brain time
            Vec2 asteroidPos = associated.box.GetCenter();
            float angle = asteroidPos.GetAngle(destination) - (M_PI / 4.0);
            speed = Vec2(rand() % 60 + 10, rand() % 60 + 10).GetRotated(angle);
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