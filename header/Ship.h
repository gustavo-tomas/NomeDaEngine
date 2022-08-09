#ifndef SHIP_H
#define SHIP_H

#include "Component.h"
#include "GameObject.h"
#include "Timer.h"

class Ship : public Component {
    public:
        Ship(GameObject& associated);
        ~Ship();
        void Start();
        void Update(float dt);
        void Shoot();
        void Render();
        bool Is(const char* type);
        void NotifyCollision(GameObject& other);
        static Ship* player;

    private:
        Timer shootTimer;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;
};

#endif // SHIP_H