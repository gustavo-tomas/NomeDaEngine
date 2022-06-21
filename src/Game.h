#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include "State.h"
#include <string>
#include <iostream>

using namespace std;

class Game {
    public:
        ~Game();

        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
    private:
        Game(const char* title, int width, int height);

        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
};

#endif // GAME_H