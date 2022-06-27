#include "../header/TileMap.h"

TileMap::TileMap(GameObject& associated, const char* file, TileSet* tileSet) : Component(associated)
{
    Load(file);
    this->tileSet = tileSet;
}

void TileMap::Load(const char* file)
{
    // @TODO
}

void TileMap::SetTileSet(TileSet* tileSet)
{
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z)
{
    // @TODO
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    // @TODO
}

void TileMap::Render()
{
    // @TODO
}

int TileMap::GetWidth()
{
    return mapWidth;
}

int TileMap::GetHeight()
{
    return mapHeight;
}

int TileMap::GetDepth()
{
    return mapDepth;
}