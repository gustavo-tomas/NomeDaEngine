#include "../header/StageState.h"
#include "../header/Game.h"
#include "../header/Sound.h"
#include "../header/Vec2.h"
#include "../header/TileSet.h"
#include "../header/TileMap.h"
#include "../header/InputManager.h"
#include "../header/Camera.h"
#include "../header/CameraFollower.h"
#include "../header/Alien.h"
#include "../header/PenguinBody.h"
#include "../header/Collider.h"
#include "../header/Collision.h"

StageState::StageState() : State()
{
    cout << "\nState created successfully!\n" << endl;
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
    Sprite* bg = new Sprite(*bgGo, "./assets/image/ocean.png");
    CameraFollower* cf = new CameraFollower(*bgGo);

    bgGo->AddComponent(bg);
    bgGo->AddComponent(cf);
    objectArray.emplace_back(bgGo);

    // Tileset & Tilemap
    GameObject* tileGo = new GameObject();
    TileSet* tileSet = new TileSet(64, 64, "./assets/image/tileset.png");
    TileMap* tileMap = new TileMap(*tileGo, "./assets/map/tileMap.txt", tileSet);
    
    tileGo->box.SetVec(Vec2(0, 0));

    tileGo->AddComponent(tileMap);
    objectArray.emplace_back(tileGo);

    // Alien
    GameObject* alienGo = new GameObject();
    Alien* alien = new Alien(*alienGo, 5);

    alienGo->box.SetVec(Vec2(512 - alienGo->box.w / 2, 300 - alienGo->box.h / 2));

    alienGo->AddComponent(alien);
    objectArray.emplace_back(alienGo);

    // Penguin
    GameObject* penguinBodyGo = new GameObject();
    PenguinBody* penguinBody = new PenguinBody(*penguinBodyGo);
    
    penguinBodyGo->box.SetVec(Vec2(704, 640));
    
    penguinBodyGo->AddComponent(penguinBody);
    objectArray.emplace_back(penguinBodyGo);

    // Camera
    Camera::Follow(penguinBodyGo);
}

void StageState::Update(float dt)
{
    // Updates the camera
    Camera::Update(dt);

    // Sets quit requested
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) ||
        InputManager::GetInstance().QuitRequested())
        quitRequested = true;    

    for (unsigned long i = 0; i < objectArray.size(); i++)
    {
        // Updates GOs
        objectArray[i]->Update(dt);
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin() + i);

        // Checks for colisions
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

void StageState::Render()
{
    RenderArray();
}

StageState::~StageState()
{
    objectArray.clear();
    cout << "Object Array deleted successfully!" << endl;
}