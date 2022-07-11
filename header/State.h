#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include <vector>
#include <memory>

using namespace std;

class State {
    public:
        State();
        ~State();
        void Start();
        weak_ptr<GameObject> AddObject(GameObject* go);
        weak_ptr<GameObject> GetObjectPtr(GameObject* go);
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

    private:
        Music music;
        bool started;
        bool quitRequested;
        vector<shared_ptr<GameObject>> objectArray;
};

#endif // STATE_H