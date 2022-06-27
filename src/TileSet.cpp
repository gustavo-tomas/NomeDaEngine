#include "../header/TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, const char* file)
{
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    GameObject* go = new GameObject();
    tileSet = new Sprite(*go, file);

    cout << "TILE W: " << this->tileWidth << endl;
    cout << "TILE H: " << this->tileHeight << endl;
    cout << "TILESET W: " << tileSet->GetWidth() << endl;
    cout << "TILESET H: " << tileSet->GetHeight() << endl;
    
    cout << "N ROWS: " << tileSet->GetHeight() / this->tileHeight << endl;
    cout << "N COLS: " << tileSet->GetWidth() / this->tileWidth << endl;

    rows = tileSet->GetHeight() / this->tileHeight;
    columns = tileSet->GetWidth() / this->tileWidth;
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
    // 0 <= index <= numOfTiles - 1
    if (index >= 0 && index <= (unsigned) rows * columns - 1)
    {
        unsigned row = index / columns;
        unsigned column = index % columns;
        tileSet->SetClip(column, row, tileWidth, tileHeight);
        tileSet->Render(x, y);    
    }
}

int TileSet::GetTileWidth()
{
    return tileWidth;
}

int TileSet::GetTileHeight()
{
    return tileHeight;    
}