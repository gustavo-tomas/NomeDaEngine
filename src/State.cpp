#include "State.h"
#include "Game.h"

State::State(): bg("./assets/image/ocean.jpg"), music("./assets/audio/stageState.ogg")
{
    quitRequested = false;
    music.Play(1);
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
        cout << "Quit requested!\n" << endl;
    }
}

void State::Render()
{
    bg.Render(0, 0);
}

bool State::QuitRequested()
{
    return quitRequested;
}