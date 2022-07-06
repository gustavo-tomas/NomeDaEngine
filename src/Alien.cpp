#include "../header/Alien.h"
#include "../header/Sprite.h"
#include "../header/InputManager.h"
#include "../header/Camera.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated)
{
    // @TODO: nMinions and action not used
    Sprite* sprite = new Sprite(associated, "./assets/image/alien.png");
    associated.AddComponent(sprite);

    speed = Vec2(0, 0);
    hp = 30;
}

void Alien::Start()
{
    // @TODO:
}

Alien::~Alien()
{
    minionArray.clear();
}

void Alien::Update(float dt)
{
    // @TODO: finish
    if (hp <= 0)
    {
        associated.RequestDelete();
        return;
    }
    
    // Checks for button press (Left = Shoot | Right = Move)
    bool leftMouse = InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON);
    bool rightMouse = InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON);

    float mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
    float mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
    
    if (leftMouse || rightMouse)
    {
        // cout << "CLICKED" << endl; // @TODO: comment
        if (leftMouse)
            taskQueue.push(Action(Action::SHOOT, mouseX, mouseY));
        else
            taskQueue.push(Action(Action::MOVE, mouseX, mouseY));
    }

    // Checks for pending actions
    if (!taskQueue.empty())
    {
        if (taskQueue.front().type == Action::SHOOT)
            taskQueue.pop();

        else if (taskQueue.front().type == Action::MOVE)
        {
            float offsetX = associated.box.w / 2;
            float offsetY = associated.box.h / 2;
            
            // cout << "TASK: MOVE" << endl; // @TODO: comment
            // Calculates distance between CurrentPos (box) <-> DesiredPos (pos)
            float xDist = (associated.box.x + offsetX) - taskQueue.front().pos.x;
            float yDist = (associated.box.y + offsetY) - taskQueue.front().pos.y;
            float dist = sqrt((xDist * xDist) + (yDist * yDist));
            
            // Calculates speed after click
            if (speed.x == 0 && speed.y == 0)
            {
                speed.x = abs((xDist / dt) / 1000);
                speed.y = abs((yDist / dt) / 1000);

                if (xDist > 0) speed.x *= -1;
                if (yDist > 0) speed.y *= -1;
            }

            float newXPos = associated.box.x + speed.x;
            float newYPos = associated.box.y + speed.y;
            float newXdist = newXPos + offsetX - taskQueue.front().pos.x;
            float newYdist = newYPos + offsetY - taskQueue.front().pos.y;
            float newDist = sqrt((newXdist * newXdist) + (newYdist * newYdist));

            // @TODO: comment
            cout << "SPEEDX: " << speed.x << "\tSPEEDY: " << speed.y << endl;
            // cout << "XDIST: " << xDist << "\tYDIST: " << yDist << endl;

            // @TODO: fix click on center
            if (dist < abs(newDist - dist))
            {
                speed.x = 0;
                speed.y = 0;
                taskQueue.pop();
                cout << "ACTION REMOVED FROM Q" << endl;
            }

            else
            {
                associated.box.x = newXPos;
                associated.box.y = newYPos;
            }
        }
    }
}

void Alien::Render()
{

}

bool Alien::Is(const char* type)
{
    string str_type = type;
    return str_type == "Alien";
}