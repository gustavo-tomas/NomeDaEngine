#include "../header/EndState.h"
#include "../header/GameData.h"
#include "../header/Sprite.h"
#include "../header/GameObject.h"
#include "../header/InputManager.h"
#include "../header/CameraFollower.h"

EndState::EndState()
{
    const char* bgFile;
    const char* musicFile;

    if (GameData::playerVictory)
    {
        bgFile = "./assets/image/win.jpg";
        musicFile = "./assets/audio/endStateWin.ogg";
    }

    else
    {
        bgFile = "./assets/image/lose.jpg";
        musicFile = "./assets/audio/endStateLose.ogg";
    }

    backgroundMusic = Music(musicFile);
    backgroundMusic.Play(1);
    
    GameObject* bgGo = new GameObject();
    Sprite* bg = new Sprite(*bgGo, bgFile);
    CameraFollower* endFollower = new CameraFollower(*bgGo);
    bgGo->AddComponent(bg);
    bgGo->AddComponent(endFollower);

    AddObject(bgGo);
}

EndState::~EndState()
{
    objectArray.clear();
}

void EndState::Update(float dt)
{
    if (InputManager::GetInstance().QuitRequested())
        quitRequested = true;

    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
        popRequested = true;
    
    UpdateArray(dt);
}

void EndState::LoadAssets()
{

}

void EndState::Render()
{
    RenderArray();
}

void EndState::Start()
{
    StartArray();
}

void EndState::Pause()
{

}

void EndState::Resume()
{

}
