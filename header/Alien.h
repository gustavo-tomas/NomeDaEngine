#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Action.h"
#include <queue>
#include <memory>

using namespace std;

class Alien : public Component {
    public:
        Alien(GameObject& associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(const char* type);

    private:
        Action* action;
        Vec2 speed;
        int hp;
        queue<Action> taskQueue;
        vector<weak_ptr<GameObject>> minionArray;
};

#endif // ALIEN_H