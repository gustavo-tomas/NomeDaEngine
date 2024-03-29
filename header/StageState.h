#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "State.h"
#include "Timer.h"
#include <vector>
#include <memory>

using namespace std;

class StageState : public State {
    public:
        StageState();
        ~StageState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
        void AddAsteroid();

    private:
        Music backgroundMusic;
        Timer quitTimer;
};

#endif // STAGESTATE_H