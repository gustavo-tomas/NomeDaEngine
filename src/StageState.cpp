#include "../header/StageState.h"
#include "../header/Game.h"
#include "../header/Sound.h"
#include "../header/Vec2.h"
#include "../header/InputManager.h"
#include "../header/Camera.h"
#include "../header/CameraFollower.h"
#include "../header/Asteroid.h"
#include "../header/Ship.h"
#include "../header/Collider.h"
#include "../header/Collision.h"
#include "../header/GameData.h"
#include "../header/EndState.h"
#include "../header/Text.h"

StageState::StageState() : State()
{
    cout << "\nStageState created successfully!\n" << endl;
}

void StageState::Start()
{
    LoadAssets();
    StartArray();
    GameData::score = 0;
    started = true;
}

void StageState::Pause()
{

}

void StageState::Resume()
{
    
}

void StageState::AddAsteroid()
{
    // Scale varies from [0.35, 0.5]
    float scale = 0.35 + ((rand() % 151) / 1000.f);
    int negative = rand() % 2;
    float rotation = M_PI / (7.0 + ((rand() % 900) / 1000.f));
    if (negative) rotation *= -1;

    GameObject* asteroidGo = new GameObject();
    Asteroid* asteroid = new Asteroid(*asteroidGo, 0.0, Vec2(scale, scale), rotation);

    asteroidGo->box.SetVec(Vec2(rand() % GameData::WIDTH * 3, rand() % GameData::HEIGHT * 3));

    asteroidGo->AddComponent(asteroid);
    AddObject(asteroidGo);
}

void StageState::LoadAssets()
{
    // Background Music
    backgroundMusic = Music("./assets/audio/stageState.ogg");
    backgroundMusic.Play();

    // Background
    GameObject* bgGo = new GameObject();
    Sprite* bg = new Sprite(*bgGo, "./assets/image/background.png");
    CameraFollower* cf = new CameraFollower(*bgGo);

    bgGo->AddComponent(bg);
    bgGo->AddComponent(cf);
    AddObject(bgGo);

    // Penguin
    GameObject* penguinBodyGo = new GameObject();
    Ship* penguinBody = new Ship(*penguinBodyGo);
    
    penguinBodyGo->box.SetVec(Vec2(704, 640));
    
    penguinBodyGo->AddComponent(penguinBody);
    AddObject(penguinBodyGo);

    // Camera
    Camera::Follow(penguinBodyGo);

    // Asteroids
    for (int i = 0; i < Asteroid::maxAsteroidCount; i++)
        AddAsteroid();

    // FPS counter
    GameObject* textGo = new GameObject();
    CameraFollower* textFollower = new CameraFollower(*textGo, textGo->box.GetVec());
    textGo->AddComponent(textFollower);

    Text* fpsText = new Text(*textGo, "./assets/font/call_me_maybe.ttf", 16, Text::BLENDED, "FPS ", {255, 255, 255, 255});
    textGo->AddComponent(fpsText);
    
    AddObject(textGo);

    // Score
    GameObject* scoreGo = new GameObject();
    scoreGo->box.SetVec(Vec2(0, 16));
    
    CameraFollower* scoreFollower = new CameraFollower(*scoreGo, scoreGo->box.GetVec());
    scoreGo->AddComponent(scoreFollower);

    Text* scoreText = new Text(*scoreGo, "./assets/font/call_me_maybe.ttf", 16, Text::BLENDED, "Score 0", {255, 255, 255, 255});
    scoreGo->AddComponent(scoreText);
    
    AddObject(scoreGo);

    // Lives
    GameObject* livesGo = new GameObject();
    livesGo->box.SetVec(Vec2(0, 32));
    
    CameraFollower* livesFollower = new CameraFollower(*livesGo, livesGo->box.GetVec());
    livesGo->AddComponent(livesFollower);

    Text* livesText = new Text(*livesGo, "./assets/font/call_me_maybe.ttf", 16, Text::BLENDED, "Lives ", {255, 255, 255, 255});
    livesGo->AddComponent(livesText);
    
    AddObject(livesGo);
}

void StageState::Update(float dt)
{
    if (QuitRequested() || PopRequested())
        return;

    // Updates the camera
    Camera::Update(dt);

    // Sets quit requested
    if (InputManager::GetInstance().QuitRequested())
        quitRequested = true;

    // Returns to title screen
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
        popRequested = true;

    // Player is dead
    if (Ship::player == nullptr && !QuitRequested() && !PopRequested())
    {
        quitTimer.Update(dt);
        if (quitTimer.Get() > 3.0)
        {
            GameData::playerVictory = false;
            Game::GetInstance().Push(new EndState());
            popRequested = true;

            pair<string, int> highScore = GameData::GetHighScore();
            if (GameData::score > highScore.second)
                GameData::SetHighScore(pair<string, int>("LOL", GameData::score));
        }
    }

    // Create Asteroids if not at maximum capacity
    if (Asteroid::asteroidCount < Asteroid::maxAsteroidCount)
        AddAsteroid();

    // Updates GOs
    UpdateArray(dt);

    for (unsigned long i = 0; i < objectArray.size(); i++)
    {
        // Updates Text - Turning into a component might be better 
        Text* text = (Text*) objectArray[i]->GetComponent("Text");
        if (text != nullptr) // Quickfix for selecting text
        {
            if (text->GetText()[0] == 'F') // FPS counter
                text->SetText(("FPS " + to_string(int(GameData::currentFPS))).c_str());
            else if (text->GetText()[0] == 'S') // Score counter
                text->SetText(("Score " + to_string(GameData::score)).c_str());
            else if (text->GetText()[0] == 'L') // Lives counter
                text->SetText(("Lives " + to_string(GameData::playerLives)).c_str());
        }
        
        // Deletes GOs
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin() + i);

        // Checks for colisions
        else
        {
            for (unsigned long j = i + 1; j < objectArray.size(); j++)
            {
                Collider* colliderA = (Collider*) objectArray[i]->GetComponent("Collider");
                Collider* colliderB = (Collider*) objectArray[j]->GetComponent("Collider");
                if (colliderA != nullptr && colliderB != nullptr)
                {
                    if (Collision::IsColliding(colliderA->box, colliderB->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg))
                    {
                        objectArray[i]->NotifyCollision(*objectArray[j]);
                        objectArray[j]->NotifyCollision(*objectArray[i]);
                    }
                }
            }
        }
    }
}

void StageState::Render()
{
    RenderArray();
}

StageState::~StageState()
{
    objectArray.clear();
    cout << "Object Array deleted successfully!" << endl;
}