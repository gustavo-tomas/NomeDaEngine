#include "../header/Camera.h"
#include "../header/InputManager.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);

void Camera::Follow(GameObject* newFocus)
{
    focus = newFocus;
}

void Camera::Unfollow()
{
    focus = nullptr;
}

void Camera::Update(float dt)
{
    if (focus != nullptr)
    {

    }

    else
    {
        // X = Xo + vo * dt + (a * dt^2) / 2
        pos.x = pos.x + speed.x * dt;
        pos.y = pos.y + speed.y * dt;
        
        float maxSpeed = 500.0;
        float incSpeed = 50.0;
        float decSpeed = 10.0;

        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) || InputManager::GetInstance().IsKeyDown(A_KEY))
            speed.x = speed.x > -maxSpeed ? speed.x - incSpeed : -maxSpeed;

        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) || InputManager::GetInstance().IsKeyDown(D_KEY))
            speed.x = speed.x < +maxSpeed ? speed.x + incSpeed : +maxSpeed;

        if (!InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) && !InputManager::GetInstance().IsKeyDown(A_KEY) &&
            !InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) && !InputManager::GetInstance().IsKeyDown(D_KEY))
        {
            speed.x = speed.x > 0 ? speed.x - decSpeed : 
                      speed.x < 0 ? speed.x + decSpeed :
                      0;
        }

        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) || InputManager::GetInstance().IsKeyDown(W_KEY))
            speed.y = speed.y > -maxSpeed ? speed.y - incSpeed : -maxSpeed;
        
        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY) || InputManager::GetInstance().IsKeyDown(S_KEY))
            speed.y = speed.y < +maxSpeed ? speed.y + incSpeed : +maxSpeed;

        if (!InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) && !InputManager::GetInstance().IsKeyDown(W_KEY) &&
            !InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY) && !InputManager::GetInstance().IsKeyDown(S_KEY))
        {
            speed.y = speed.y > 0 ? speed.y - decSpeed : 
                      speed.y < 0 ? speed.y + decSpeed :
                      0;
        }
    }
}