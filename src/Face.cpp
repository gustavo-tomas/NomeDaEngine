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
        cout << "Enemy killed!\n" << endl;
        Sound* sound = (Sound *) associated.GetComponent("Sound");

        // O som e tocado mas o objeto e deletado logo apos, entao
        // parece que o som nao toca. So um detalhe da implementacao
        // do Trab2
        if (sound != nullptr)
        {
            sound->Play();
            cout << "Playing sound!" << endl;
        }
        associated.RequestDelete(); // Comente essa linha para ouvir o som de morte
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