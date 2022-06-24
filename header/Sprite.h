#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include "Component.h"
#include <iostream>

using namespace std;

class Sprite : public Component {
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, const char* file);
        ~Sprite();
        void Open(const char* file);
        void SetClip(int x, int y, int w, int h);
        void Update(float dt);
        bool Is(const char* type);
        void Render();
        int GetWidth();
        int GetHeight();
        bool IsOpen();

    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};

#endif // SPRITE_H