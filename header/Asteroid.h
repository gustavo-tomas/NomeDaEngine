#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"
#include <queue>
#include <memory>

using namespace std;

class Asteroid : public Component {
    public:
        Asteroid(GameObject& associated, float timeOffset = 0, Vec2 scale = Vec2(1.0, 1.0), float rotation = M_PI / 10.0);
        ~Asteroid();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(const char* type);
        void NotifyCollision(GameObject& other);
        static int asteroidCount;
        const static int maxAsteroidCount;

    private:
        enum AsteroidState {
            MOVING,
            RESTING
        };
        AsteroidState state;
        Timer restTimer;
        Vec2 destination;
        Vec2 speed;
        Vec2 scale;
        int hp;
        float timeOffset;
        float rotation;
        float distanceLeft = 2000;
};

#endif // ALIEN_H