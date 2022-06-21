#include "Game.h"

const int WIDTH = 1024;
const int HEIGHT = 600;
const char* TITLE = "Gustavo Tomas de Paula - 190014148";

Game* Game::instance = nullptr;

Game::Game(const char* title, int width, int height)
{
    if (instance != nullptr)
    {
        cout << "A game instance already exists" << endl;
        exit(1);
    }
    else
    {
        instance = this;
        cout << "First and only instance created successfully!" << endl;
    }

    // Initializes SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        cout << "Error initializing SDL" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "SDL initialized successfully!" << endl;

    // Initializes SDL_Image
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0)
    {
        cout << "Error initializing IMG" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "IMG initialized successfully!" << endl;

    // Initializes SDL_Mixer
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0)
    {
        cout << "Error initializing MIX" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "MIX initialized successfully!" << endl;

    // Initializes OpenAudio
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        cout << "Error initializing OpenAudio" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "OpenAudio initialized successfully!" << endl;

    // Allocates audio channels
    Mix_AllocateChannels(32);

    // Creates game window
    if ((window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0)) == nullptr)
    {
        cout << "Error creating window" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "Window created successfully!" << endl;

    // Creates renderer
    if ((renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED)) == nullptr)
    {
        cout << "Error creating renderer" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else
        cout << "Renderer created successfully!" << endl;

    // Creates state
    state = new State(renderer); // @TODO: fix this
}

Game& Game::GetInstance()
{
    if (instance == nullptr)
        instance = new Game(TITLE, WIDTH, HEIGHT);

    return *instance;
}

State& Game::GetState()
{
    return *state;
}

SDL_Renderer* Game::GetRenderer()
{
    return renderer;
}

void Game::Run()
{
    cout << endl << "Engine running!" << endl;
    while (state->QuitRequested() == false)
    {
        // @TODO: define dt in Update(dt)
        state->Update(0);
        state->Render();

        SDL_RenderPresent(renderer);
        SDL_Delay(33); // 30 FPS
    }
    this->~Game();
}

Game::~Game()
{
    delete state;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    cout << "Instance deleted successfully!" << endl;
}
