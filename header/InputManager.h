#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define INCLUDE_SDL
#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

#define SPACE_KEY         SDLK_SPACE

#include "SDL_include.h"
#include <unordered_map>

using namespace std;

class InputManager {
    public:
        static InputManager& GetInstance();
        void Update();
        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);
        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);
        int GetMouseX();
        int GetMouseY();
        bool QuitRequested();

    private:
        InputManager();
        ~InputManager();
        unordered_map<int, bool> keyState;
        unordered_map<int, int> keyUpdate;
        bool mouseState[6];
        int mouseUpdate[6];
        bool quitRequested;
        int updateCounter;
        int mouseX;
        int mouseY;
};

#endif // INPUTMANAGER_H