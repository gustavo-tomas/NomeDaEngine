#include "../header/StageState.h"
#include "../header/Game.h"
#include "../header/Sound.h"
#include "../header/Vec2.h"
#include "../header/TileSet.h"
#include "../header/TileMap.h"
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
    started = true;
}

void StageState::Pause()
{

}

void StageState::Resume()
{
    
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
    {
        GameObject* asteroidGo = new GameObject();
        Asteroid* asteroid = new Asteroid(*asteroidGo);

        asteroidGo->box.SetVec(Vec2(rand() % GameData::WIDTH * 2, rand() % GameData::HEIGHT * 2));

        asteroidGo->AddComponent(asteroid);
        AddObject(asteroidGo);
    }

    // FPS counter
    GameObject* textGo = new GameObject();
    CameraFollower* textFollower = new CameraFollower(*textGo, textGo->box.GetVec());
    textGo->AddComponent(textFollower);

    const char* fontFile = "./assets/font/call_me_maybe.ttf";
    const char* textStr = "FPS ";
    int fontSize = 16;
    Text::TextStyle style = Text::BLENDED;
    SDL_Color color = {212, 15, 15, 255};
    
    Text* text = new Text(*textGo, fontFile, fontSize, style, textStr, color);
    textGo->AddComponent(text);
    
    AddObject(textGo);
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
    if (Ship::player == nullptr && !QuitRequested())
    {
        GameData::playerVictory = false;
        Game::GetInstance().Push(new EndState());
        popRequested = true;
    }

    // Create Asteroids if not at maximum capacity
    if (Asteroid::asteroidCount < Asteroid::maxAsteroidCount)
    {
        GameObject* asteroidGo = new GameObject();
        Asteroid* asteroid = new Asteroid(*asteroidGo);

        asteroidGo->box.SetVec(Vec2(rand() % GameData::WIDTH, rand() % GameData::HEIGHT));

        asteroidGo->AddComponent(asteroid);
        AddObject(asteroidGo);
    }

    // Updates GOs
    UpdateArray(dt);

    for (unsigned long i = 0; i < objectArray.size(); i++)
    {
        // Deletes GOs
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin() + i);

        // Updates FPS counter - Turning into a component might be better 
        Text* FPS_Text = (Text*) objectArray[i]->GetComponent("Text");
        if (FPS_Text != nullptr)
            FPS_Text->SetText(("FPS " + to_string(int(GameData::currentFPS))).c_str());

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