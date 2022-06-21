#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"

using namespace std;

class State {
    public:
        State();
        State(SDL_Renderer* renderer); // @TODO: fix this
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
    private:
        Sprite bg;
        Music* music; // @TODO: fix this
        Music music1;
        bool quitRequested;

        
        SDL_Renderer* renderer; // @TODO: fix this
};

#endif // STATE_H