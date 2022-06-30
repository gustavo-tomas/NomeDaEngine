#include "../header/Face.h"
#include "../header/Sound.h"
#include "../header/InputManager.h"

Face::Face(GameObject& associated) : Component(associated)
{
    hitpoints = 30;
}

void Face::Damage(int damage)
{
    if ((hitpoints -= damage) <= 0)
    {
        Sound* sound = (Sound *) associated.GetComponent("Sound");

        if (sound != nullptr)
            sound->Play();
    }
    cout << "HP is " << hitpoints << endl;
}

void Face::Update(float dt)
{
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) &&
        associated.box.Contains({ 
            (float) InputManager::GetInstance().GetMouseX(),
            (float) InputManager::GetInstance().GetMouseY()
        })
    ) 
    {
        Damage(rand() % 10 + 10);
    }

    if (hitpoints <= 0)
    {
        Sound* sound = (Sound *) associated.GetComponent("Sound");

        if (sound == nullptr || (sound != nullptr && !sound->IsOpen()))
            associated.RequestDelete();
    }
}

void Face::Render()
{
    
}

bool Face::Is(const char* type)
{
    string str_type = type;
    return (str_type == "Face");
}