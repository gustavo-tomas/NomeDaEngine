#include "../header/Face.h"
#include "../header/Sound.h"

Face::Face(GameObject& associated) : Component(associated)
{
    hitpoints = 30;
}

void Face::Damage(int damage)
{
    if ((hitpoints -= damage) <= 0)
    {
        cout << "\nEnemy killed!" << endl;
        Sound* sound = (Sound *) associated.GetComponent("Sound");
        if (sound != nullptr)
        {
            sound->Play(); // @TODO: fix this
            cout << "Playing sound!" << endl;
        }
        associated.RequestDelete();
    }
    else
        cout << "HP is " << hitpoints << endl;
}

void Face::Update(float dt)
{

}

void Face::Render()
{
    
}

bool Face::Is(const char* type)
{
    string str_type = type;
    return (str_type == "Face");
}