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
        Sound* sound = (Sound *) associated.GetComponent("Sound");

        if (sound != nullptr)
            sound->Play();
    }
    cout << "HP is " << hitpoints << endl;
}

// Como face e uma classe temporaria, o request delete foi
// movido de damage para update para melhorar o funcionamento do jogo.
void Face::Update(float dt)
{
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