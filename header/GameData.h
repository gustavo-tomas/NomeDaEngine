#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Timer.h"
#include <string>
#include <utility>

using namespace std;

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
        
        static pair<string, int> GetHighScore();
        static void SetHighScore(pair<string, int> score);
};

#endif // GAMEDATA_H