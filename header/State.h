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
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

    private:
        void Input();
        void AddObject(int mouseX, int mouseY);
        Music music;
        bool quitRequested;
        vector<unique_ptr<GameObject>> objectArray;
};

#endif // STATE_H