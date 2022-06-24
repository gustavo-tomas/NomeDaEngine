#include "../header/Sound.h"

Sound::Sound(GameObject& associated) : Component(associated)
{
    chunk = nullptr;
}

Sound::Sound(GameObject& associated, const char* file) : Sound(associated)
{
    Open(file);
}

void Sound::Play(int times)
{
    channel = Mix_PlayChannel(-1, chunk, times);
}

void Sound::Stop()
{
    if (chunk != nullptr)
        Mix_HaltChannel(channel);
}

void Sound::Open(const char* file)
{
    if ((chunk = Mix_LoadWAV(file)) == nullptr)
    {
        cout << "Error loading sound" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "Sound " << file << " loaded successfully!" << endl;
}

Sound::~Sound()
{
    if (chunk != nullptr)
    {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
        cout << "Sound deleted successfully!" << endl;
    }
    else
        cout << "Sound chunk is already null!" << endl;
}

void Sound::Update(float dt)
{

}

void Sound::Render()
{
    
}

bool Sound::Is(const char* type)
{
    string str_type = type;
    return (str_type == "Sound");
}