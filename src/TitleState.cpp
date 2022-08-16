#include "../header/TitleState.h"
#include "../header/GameObject.h"
#include "../header/Sprite.h"
#include "../header/InputManager.h"
#include "../header/Game.h"
#include "../header/StageState.h"
#include "../header/CameraFollower.h"
#include "../header/Text.h"

#include <iomanip>
#include <sstream>
#include <string>

TitleState::TitleState() : State()
{
    GameObject* titleGo = new GameObject();
    Sprite* titleSprite = new Sprite(*titleGo, "./assets/image/cover60/0001.png");
    CameraFollower* titleFollower = new CameraFollower(*titleGo);
    titleGo->AddComponent(titleSprite);
    titleGo->AddComponent(titleFollower);

    GameObject* textGo = new GameObject();
    textGo->box.SetVec(Vec2(100, 450));
    CameraFollower* textFollower = new CameraFollower(*textGo, textGo->box.GetVec());
    textGo->AddComponent(textFollower);

    const char* fontFile = "./assets/font/call_me_maybe.ttf";
    const char* textStr = "press space to continue";
    int fontSize = 32;
    Text::TextStyle style = Text::BLENDED;
    SDL_Color color = {255, 255, 255, 255};
    
    Text* text = new Text(*textGo, fontFile, fontSize, style, textStr, color, 0.75);
    textGo->AddComponent(text);
    
    this->titleSprite = titleSprite;
    this->titleSpriteCounter = 0;

    AddObject(titleGo);
    AddObject(textGo);
}

TitleState::~TitleState()
{
    objectArray.clear();
}

void TitleState::LoadAssets()
{

}

void TitleState::Update(float dt)
{
    // Updates timer
    titleSpriteTimer.Update(dt);

    // Sets quit requested
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) ||
        InputManager::GetInstance().QuitRequested())
        quitRequested = true;

    // Creates new StageState
    if (InputManager::GetInstance().KeyPress(SPACE_KEY))
        Game::GetInstance().Push(new StageState());

    // Changes background image
    if (titleSpriteTimer.Get() >= 0.25)
    {
        titleSpriteCounter = (titleSpriteCounter + 1) % 61;
        if (titleSpriteCounter == 0) titleSpriteCounter++;
        
        ostringstream fileStream;
        fileStream << setw(4) << setfill('0') << titleSpriteCounter;

        string file = "./assets/image/cover60/" + fileStream.str() + ".png";
        this->titleSprite->Open(file);
        titleSpriteTimer.Restart();
    }

    UpdateArray(dt);
}

void TitleState::Render()
{
    RenderArray();
}

void TitleState::Start()
{
    StartArray();
}

void TitleState::Pause()
{

}

void TitleState::Resume()
{

}
