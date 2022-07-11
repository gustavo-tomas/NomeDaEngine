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
    float arcOffSet = (2.0 * M_PI) / hp;

    for (int i = 0; i < hp; i++)
    {
        GameObject* minionGo = new GameObject();
        Minion* minion = new Minion(*minionGo, alienPtr, arcOffSet * (float) i);

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
    
    associated.angleDeg -= 30 * dt;

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
            }
            cout << "SHOOT REMOVED FROM Q" << endl;
            taskQueue.pop();
        }

        else if (taskQueue.front().type == Action::MOVE)
        {
            // Calculates distance between CurrentPos (box) <-> DesiredPos (pos)
            Vec2 alienPos = associated.box.GetCenter();
            Vec2 pos = taskQueue.front().pos;
            float dist = alienPos.GetDistance(pos);
            
            // First time calculating angle
            if (speed.x == 0 && speed.y == 0)
            {
                float angle = alienPos.GetAngle(pos) - (M_PI / 4.0);
                speed = Vec2(400, 400).GetRotated(angle);
            }

            Vec2 newPos = alienPos + (speed * dt);
            float newDist = newPos.GetDistance(pos);

            if (dist >= abs(dist - newDist))
                associated.box.SetVec(associated.box.GetVec() + (speed * dt));

            else
            {
                speed = Vec2(0, 0);
                taskQueue.pop();
                cout << "MOVE REMOVED FROM Q" << endl;
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