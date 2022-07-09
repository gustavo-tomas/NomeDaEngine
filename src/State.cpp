#include "../header/State.h"
#include "../header/Game.h"
#include "../header/Sound.h"
#include "../header/Vec2.h"
#include "../header/TileSet.h"
#include "../header/TileMap.h"
#include "../header/InputManager.h"
#include "../header/Camera.h"
#include "../header/CameraFollower.h"
#include "../header/Alien.h"

State::State() :
    music("./assets/audio/stageState.ogg")
{
    // Start variables
    started = false;
    quitRequested = false;
    music.Play(1);

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
    
    tileGo->box.x = 0;
    tileGo->box.y = 0;

    tileGo->AddComponent(tileMap);
    objectArray.emplace_back(tileGo);

    // Alien
    GameObject* alienGo = new GameObject();
    Alien* alien = new Alien(*alienGo, 5);

    alienGo->box.SetVec(Vec2(512 - alienGo->box.w / 2, 300 - alienGo->box.h / 2));

    alienGo->AddComponent(alien);
    objectArray.emplace_back(alienGo);

    cout << "\nState created successfully!\n" << endl;
}

void State::Start()
{
    LoadAssets();
    for (auto& obj : objectArray)
        obj->Start();
    started = true;
}

void State::LoadAssets()
{

}

void State::Update(float dt)
{
    // Updates the camera
    Camera::Update(dt);

    // Set quit requested
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) ||
        InputManager::GetInstance().QuitRequested())
        quitRequested = true;    

    for (long unsigned int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin() + i);
    }
}

void State::Render()
{
    for (auto& object : objectArray)
        object->Render();
}

weak_ptr<GameObject> State::AddObject(GameObject* go)
{
    auto ptr = shared_ptr<GameObject>(go);
    objectArray.push_back(ptr);
    if (started)
        go->Start();
    
    return weak_ptr<GameObject>(ptr);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go)
{
    for (auto& obj : objectArray)
    {
        if (obj.get() == go)
            return weak_ptr<GameObject>(obj);
    }
    return weak_ptr<GameObject>();
}

bool State::QuitRequested()
{
    return quitRequested;
}

State::~State()
{
    objectArray.clear();
    cout << "Object Array deleted successfully!" << endl;
}