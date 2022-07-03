#include "../header/Camera.h"
#include "../header/InputManager.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);

Camera& Camera::GetInstance()
{
    static Camera instance;
    return instance;
}

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
        // @TODO: finish
        // pos = Vec2(
        //     focus->box.x - 512 + focus->box.w / 2,
        //     focus->box.y - 300 + focus->box.h / 2
        // );
    }

    else
    {
        // X = Xo + vo * dt + (a * dt^2) / 2
        pos.x = pos.x + speed.x * dt;
        pos.y = pos.y + speed.y * dt;
        
        float maxSpeed = 250.0;
        float incSpeed = 30.0;
        float decSpeed = 10.0;

        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
            speed.x = speed.x < maxSpeed ? speed.x + incSpeed : maxSpeed;

        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
            speed.x = speed.x > -maxSpeed ? speed.x - incSpeed : -maxSpeed;

        if (!InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) &&
            !InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
        {
            speed.x = speed.x > 0 ? speed.x - decSpeed : 
                      speed.x < 0 ? speed.x + decSpeed :
                      0;
        }

        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
            speed.y = speed.y < maxSpeed ? speed.y + incSpeed : maxSpeed;
        
        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
            speed.y = speed.y > -maxSpeed ? speed.y - incSpeed : -maxSpeed;

        if (!InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) &&
            !InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
        {
            speed.y = speed.y > 0 ? speed.y - decSpeed : 
                      speed.y < 0 ? speed.y + decSpeed :
                      0;
        }
    }
    cout << "POSX: " << pos.x << " POSY: " << pos.y << endl;
}