#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF

#include "SDL_include.h"
#include "Game.h"
#include <unordered_map>

using namespace std;

class Resources {
    public:
        static SDL_Texture* GetImage(const char* file);
        static Mix_Music* GetMusic(const char* file);
        static Mix_Chunk* GetSound(const char* file);
        static TTF_Font* GetFont(const char* file, int fontSize);
        static void ClearImages();
        static void ClearMusics();
        static void ClearSounds();
        static void ClearFonts();

    private:
        static unordered_map<const char*, SDL_Texture*> imageTable;
        static unordered_map<const char*, Mix_Music*> musicTable;
        static unordered_map<const char*, Mix_Chunk*> soundTable;
        static unordered_map<const char*, TTF_Font*> fontTable;
};

#endif // RESOURCES_H