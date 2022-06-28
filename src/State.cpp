#include "../header/State.h"
#include "../header/Game.h"
#include "../header/Sound.h"
#include "../header/Face.h"
#include "../header/Vec2.h"
#include "../header/TileSet.h"
#include "../header/TileMap.h"

State::State() :
    music("./assets/audio/stageState.ogg")
{
    // Tileset & Tilemap
    GameObject* tileGo = new GameObject();
    TileSet* tileSet = new TileSet(64, 64, "./assets/image/tileset.png"); // @TODO: delete tileset when finished
    TileMap* tileMap = new TileMap(*tileGo, "./assets/map/tileMap.txt", tileSet);
    
    tileGo->box.x = 0;
    tileGo->box.y = 0;

    tileGo->AddComponent(tileMap);
    objectArray.emplace_back(tileGo);

    AddObject(100, 200);

    quitRequested = false;
    music.Play(1);
    cout << "\nState created successfully!\n" << endl;
}

void State::LoadAssets()
{

}

void State::Update(float dt)
{
    Input();

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

void State::Input()
{
    SDL_Event event;
	int mouseX, mouseY;

	// Mouse coordinates
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent returns 1 if any event is found, 0 otherwise
	while (SDL_PollEvent(&event)) {

		// If event is quit
		if (event.type == SDL_QUIT)
			quitRequested = true;
		
		// If event is a mouse click
		if (event.type == SDL_MOUSEBUTTONDOWN) {

			// Get the object on top
			for (int i = objectArray.size() - 1; i >= 0; i--)
            {
				// Get pointer and casts to Face. (DONT USE GET)
				GameObject* go = (GameObject*) objectArray[i].get();
				
				if(go->box.Contains({ (float) mouseX, (float) mouseY }))
                {
					Face* face = (Face*) go->GetComponent("Face");
                    if (nullptr != face)
                    {
						// Deals massive damage
						face->Damage(rand() % 10 + 10);
						// Hits only one target
						break;
					}
				}
			}
		}

        // If event type is a key
		if (event.type == SDL_KEYDOWN)
        {
			// If key is "ESC", quits
			if(event.key.keysym.sym == SDLK_ESCAPE)
				quitRequested = true;

			// Else creates objects
			else
            {
				Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI*(rand() % 1001)/500.0) + Vec2(mouseX, mouseY);
				AddObject((int) objPos.x, (int) objPos.y);
			}
		}
	}
}

State::~State()
{
    objectArray.clear();
    cout << "Object Array deleted successfully!" << endl;
}