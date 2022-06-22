#include "Music.h"

Music::Music()
{
    music = nullptr;
}

Music::Music(const char* file)
{
    music = nullptr;
    Open(file);
}

void Music::Play(int times)
{
    if (Mix_PlayMusic(music, times) < 0)
    {
        cout << "Error playing music" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "Music played successfully!" << endl;
}

void Music::Stop(int msToStop)
{
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(const char* file)
{
    if ((music = Mix_LoadMUS(file)) == nullptr)
    {
        cout << "Error loading music " << file << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "Music " << file << " loaded successfully!" << endl;
}

bool Music::IsOpen()
{
    if (music == nullptr)
        return true;
    return false;
}

Music::~Music()
{
    Stop();
    Mix_FreeMusic(music);
    cout << "Music freed successfully!" << endl;
}