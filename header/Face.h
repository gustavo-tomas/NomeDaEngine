#ifndef FACE_H
#define FACE_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include <iostream>

class Face : public Component {
    public:
        Face(GameObject& associated);
        void Damage(int damage);
        void Update(float dt);
        void Render();
        bool Is(const char* type);

    private:
        int hitpoints;
        Vec2 initialPos; // @TODO: fix this
};

#endif // FACE_H