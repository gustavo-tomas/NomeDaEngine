#include "../header/Alien.h"
#include "../header/Sprite.h"
#include "../header/InputManager.h"
#include "../header/Camera.h"
#include "../header/Minion.h"
#include "../header/Game.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated)
{
    Sprite* sprite = new Sprite(associated, "./assets/image/alien.png");
    associated.AddComponent(sprite);

    speed = Vec2(0, 0);
    hp = nMinions; // Number of minions = HP of the alien
}

void Alien::Start()
{
    State& state = Game::GetInstance().GetState();
    auto alienPtr = state.GetObjectPtr(&associated); 
    
    for (int i = 0; i < hp; i++)
    {
        GameObject* minionGo = new GameObject();
        Minion* minion = new Minion(*minionGo, alienPtr, i);
        
        minionGo->AddComponent(minion);
        auto minionPtr = state.AddObject(minionGo);
        minionArray.push_back(minionPtr);
    }
}

Alien::~Alien()
{
    minionArray.clear();
}

void Alien::Update(float dt)
{
    if (hp <= 0)
    {
        associated.RequestDelete();
        return;
    }
    
    associated.angleDeg -= 30 * dt; // @TODO: fix?

    // Checks for button press (Left = Shoot | Right = Move)
    bool leftMouse = InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON);
    bool rightMouse = InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON);

    float mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
    float mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
    
    if (leftMouse || rightMouse)
    {
        if (leftMouse)
            taskQueue.push(Action(Action::SHOOT, mouseX, mouseY));
        else
            taskQueue.push(Action(Action::MOVE, mouseX, mouseY));
    }

    // Checks for pending actions
    if (!taskQueue.empty())
    {
        // Shoots if any minions are alive
        if (taskQueue.front().type == Action::SHOOT)
        {
            if (minionArray.size() > 0)
            {
                // Get minion closest to pos
                int idx = 0;
                float shortestDist = 1000000;
                for (unsigned int i = 0; i < minionArray.size(); i++)
                {
                    float dist = minionArray[i].lock()->box.GetCenter().GetDistance(taskQueue.front().pos);
                    shortestDist = min(shortestDist, dist);
                    if (shortestDist == dist)
                        idx = i;
                }
                auto minion = (Minion *) minionArray[idx].lock()->GetComponent("Minion");
                auto target = taskQueue.front().pos;
                
                minion->Shoot(target);
                cout << "IDX: " << idx << " SHOOTING: " << target.x << ", " << target.y << endl;
            }
            cout << "SHOOT REMOVED FROM Q" << endl;
            taskQueue.pop();
        }

        else if (taskQueue.front().type == Action::MOVE)
        {
            // Calculates distance between CurrentPos (box) <-> DesiredPos (pos)
            Vec2 vDist = associated.box.GetCenter();
            Vec2 pos = Vec2(taskQueue.front().pos.x, taskQueue.front().pos.y);
            float dist = vDist.GetDistance(pos);
            
            // Calculates speed after click
            if (speed.x == 0 && speed.y == 0)
            {
                float xDist = vDist.x - pos.x;
                float yDist = vDist.y - pos.y;
                
                speed.x = abs((xDist / dt) / 1000);
                speed.y = abs((yDist / dt) / 1000);

                if (xDist > 0) speed.x *= -1;
                if (yDist > 0) speed.y *= -1;
            }

            Vec2 newPos = associated.box.GetCenter() + speed;
            float newDist = newPos.GetDistance(pos);

            // @TODO: fix click on center
            if (dist < abs(newDist - dist))
            {
                speed.x = 0;
                speed.y = 0;
                taskQueue.pop();
                cout << "MOVE REMOVED FROM Q" << endl;
            }

            else
            {
                associated.box.x += speed.x;
                associated.box.y += speed.y;
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