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
        // center of the screen
    }

    else
    {
        int dX = 64, dY = 64;
        // @TODO: update position and speed
        if (InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY))
            pos = pos + Vec2(dX, 0);

        if (InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY))
            pos = pos - Vec2(dX, 0);

        if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY))
            pos = pos + Vec2(0, dY);

        if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY))
            pos = pos - Vec2(0, dY);

        cout << "POSX: " << pos.x << " POSY: " << pos.y << endl;
    }
}