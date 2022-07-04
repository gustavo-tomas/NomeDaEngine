#include "../header/State.h"
#include "../header/Game.h"
#include "../header/Sound.h"
#include "../header/Face.h"
#include "../header/Vec2.h"
#include "../header/TileSet.h"
#include "../header/TileMap.h"
#include "../header/InputManager.h"
#include "../header/Camera.h"
#include "../header/CameraFollower.h"

State::State() :
    music("./assets/audio/stageState.ogg")
{
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

    quitRequested = false;
    music.Play(1);
    cout << "\nState created successfully!\n" << endl;
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

    // Create a face if space is pressed
    if (InputManager::GetInstance().KeyPress(SPACE_KEY))
    {
        Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI*(rand() % 1001)/500.0) + Vec2(
            InputManager::GetInstance().GetMouseX() + Camera::pos.x,
            InputManager::GetInstance().GetMouseY() + Camera::pos.y);
        AddObject((int) objPos.x, (int) objPos.y);
    }

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

void State::AddObject(int mouseX, int mouseY)
{
    GameObject* go = new GameObject();
    go->box.x = mouseX;
    go->box.y = mouseY;

    Sprite* sprite = new Sprite(*go, "./assets/image/penguinface.png");
    go->AddComponent(sprite);

    Sound* sound = new Sound(*go, "./assets/audio/boom.wav");
    go->AddComponent(sound);

    Face* face = new Face(*go);
    go->AddComponent(face);

    objectArray.emplace_back(go);
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