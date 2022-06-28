#include "../header/GameObject.h"

GameObject::GameObject()
{
    isDead = false;
}

GameObject::~GameObject()
{
    components.clear();
    cout << "Game Object deleted successfully!" << endl;
}

void GameObject::Update(float dt)
{
    for (auto& cpt : components)
        cpt->Update(dt);
}

void GameObject::Render()
{
    for (auto& cpt : components)
        cpt->Render();
}

bool GameObject::IsDead()
{
    return isDead;
}

void GameObject::RequestDelete()
{
    isDead = true;
}

void GameObject::AddComponent(Component* cpt)
{
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt)
{
    components.erase(
        remove_if(components.begin(), components.end(),
            [&](unique_ptr<Component> &component) { return component.get() == cpt; }
        ),
        components.end()
    );
}

Component* GameObject::GetComponent(const char* type)
{
    for (auto& cpt : components)
        if (cpt->Is(type))
            return cpt.get();

    return nullptr;
}