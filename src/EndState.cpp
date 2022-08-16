#include "../header/EndState.h"
#include "../header/GameData.h"
#include "../header/Sprite.h"
#include "../header/GameObject.h"
#include "../header/InputManager.h"
#include "../header/CameraFollower.h"
#include "../header/Text.h"

EndState::EndState()
{
    // Chooses background depending on the ending
    const char* bgFile = "./assets/image/end.png";
    
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
    if (InputManager::GetInstance().QuitRequested() ||
        InputManager::GetInstance().KeyPress(ESCAPE_KEY))
        quitRequested = true;

    if (InputManager::GetInstance().KeyPress(SPACE_KEY))
        popRequested = true;
    
    UpdateArray(dt);
}

void EndState::LoadAssets()
{
    // Chooses music depending on the ending
    const char* musicFile;

    if (GameData::playerVictory)
        musicFile = "./assets/audio/endStateWin.ogg";

    else
        musicFile = "./assets/audio/endStateLose.ogg";

    backgroundMusic = Music(musicFile);
    backgroundMusic.Play(1);

    // Writes text
    GameObject* textGo = new GameObject();
    textGo->box.SetVec(Vec2(100, 450));
    CameraFollower* textFollower = new CameraFollower(*textGo, textGo->box.GetVec());
    textGo->AddComponent(textFollower);

    const char* fontFile = "./assets/font/call_me_maybe.ttf";
    const char* textStr = "press esc to quit or space to go back to title";
    int fontSize = 32;
    Text::TextStyle style = Text::BLENDED;
    SDL_Color color = {255, 255, 255, 255};
    
    Text* text = new Text(*textGo, fontFile, fontSize, style, textStr, color, 1.0);
    textGo->AddComponent(text);
    
    // Score
    GameObject* scoreTextGo = new GameObject();
    scoreTextGo->box.SetVec(Vec2(100, 400));

    CameraFollower* scoreTextFollower = new CameraFollower(*scoreTextGo, scoreTextGo->box.GetVec());
    scoreTextGo->AddComponent(scoreTextFollower);
    
    Text* scoreText = new Text(*scoreTextGo, fontFile, fontSize, style, "your score " + to_string(GameData::score), color);
    scoreTextGo->AddComponent(scoreText);

    // High Score
    GameObject* highScoreTextGo = new GameObject();
    highScoreTextGo->box.SetVec(Vec2(100, 350));

    CameraFollower* highScoreTextFollower = new CameraFollower(*highScoreTextGo, highScoreTextGo->box.GetVec());
    highScoreTextGo->AddComponent(highScoreTextFollower);
    
    Text* highScoreText = new Text(*highScoreTextGo, fontFile, fontSize, style, "Highscore " + to_string(GameData::GetHighScore().second), color);
    highScoreTextGo->AddComponent(highScoreText);

    AddObject(highScoreTextGo);
    AddObject(scoreTextGo);
    AddObject(textGo);
}

void EndState::Render()
{
    RenderArray();
}

void EndState::Start()
{
    LoadAssets();
    StartArray();
}

void EndState::Pause()
{

}

void EndState::Resume()
{

}
