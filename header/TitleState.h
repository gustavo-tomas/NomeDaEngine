#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
#include "Timer.h"
#include "Sprite.h"

class TitleState : public State {
    public:
        TitleState();
        ~TitleState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();

    private:
        Sprite* titleSprite;
        Timer titleSpriteTimer;
        int titleSpriteCounter;
};

#endif // TITLESTATE_H