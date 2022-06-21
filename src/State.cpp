#include "State.h"

State::State()
{
    quitRequested = false;
    bg = Sprite("path_to_file", renderer); // @TODO: define a sprite
    cout << "State created successfully!" << endl;
}

// @TODO: fix this
State::State(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    quitRequested = false;
    bg = Sprite("./assets/image/ocean.jpg", renderer); // @TODO: fix this
    music = new Music("./assets/audio/stageState.ogg"); // @TODO: fix this
    // music1 = Music("./assets/audio/stageState.ogg");
    // music = new Music("./assets/audio/choochoo.wav"); // @TODO: debug
    
    (*music).Play(1);
    // music1.Play(1);

    cout << "State created successfully!" << endl;
}

void State::LoadAssets()
{

}

void State::Update(float dt)
{
    if (SDL_QuitRequested() == true)
    {
        quitRequested = true;
        cout << "Quit requested!" << endl;
    }
}

void State::Render()
{
    bg.Render(0, 0); // @TODO: fix this
}

bool State::QuitRequested()
{
    return quitRequested;
}