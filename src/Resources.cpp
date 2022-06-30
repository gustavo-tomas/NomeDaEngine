#include "../header/Resources.h"

// Create resources
unordered_map<const char*, SDL_Texture*> Resources::imageTable;
unordered_map<const char*, Mix_Music*> Resources::musicTable;
unordered_map<const char*, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(const char* file)
{
    // Check if texture is already loaded
    if (imageTable.find(file) != imageTable.end())
        return imageTable[file];
    
    SDL_Texture* texture;
    if ((texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file)) == nullptr)
    {
        cout << "Error loading texture " << file << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }

    else
    {
        imageTable[file] = texture;
        cout << "\nTexture " << file << " loaded successfully!" << endl;
        return imageTable[file];
    }
}

Mix_Music* Resources::GetMusic(const char* file)
{
    // Check if music is already loaded
    if (musicTable.find(file) != musicTable.end())
        return musicTable[file];
    
    Mix_Music* music;
    if ((music = Mix_LoadMUS(file)) == nullptr)
    {
        cout << "Error loading music " << file << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }

    else
    {
        musicTable[file] = music;
        cout << "\nMusic " << file << " loaded successfully!" << endl;
        return musicTable[file];
    }
}

Mix_Chunk* Resources::GetSound(const char* file)
{
    // Check if sound is already loaded
    if (soundTable.find(file) != soundTable.end())
        return soundTable[file];
    
    Mix_Chunk* chunk;
    if ((chunk = Mix_LoadWAV(file)) == nullptr)
    {
        cout << "Error loading sound" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }

    else
    {
        soundTable[file] = chunk;
        cout << "\nSound " << file << " loaded successfully!" << endl;
        return soundTable[file];
    }
}

void Resources::ClearImages()
{
    for (auto i : imageTable)
        SDL_DestroyTexture(i.second);

    imageTable.clear();
    cout << "Textures destroyed successfully!" << endl;
}

void Resources::ClearMusics()
{
    for (auto m : musicTable)
        Mix_FreeMusic(m.second);

    musicTable.clear();
    cout << "Musics freed successfully!" << endl;
}

void Resources::ClearSounds()
{
    for (auto c : soundTable)
        Mix_FreeChunk(c.second);

    soundTable.clear();
    cout << "Sounds freed successfully!" << endl;
}