#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include <iostream>

using namespace std;

class Sprite {
    public:
        Sprite();
        Sprite(const char* file);
        ~Sprite();
        void Open(const char* file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y);
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