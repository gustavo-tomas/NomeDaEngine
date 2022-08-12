#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Timer.h"

class GameData {
    public:
        static const int WIDTH;
        static const int HEIGHT;
        static const char* TITLE;
        static bool playerVictory;
        static float targetFPS;
        static float currentFPS;
        static float delay;
        static int score;
        static int playerLives;
};

#endif // GAMEDATA_H