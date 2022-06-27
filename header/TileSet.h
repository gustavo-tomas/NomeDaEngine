#ifndef TILESET_H
#define TILESET_H

#include "Sprite.h"
#include "GameObject.h"

class TileSet {
    public:
        TileSet(int tileWidth, int tileHeight, const char* file);
        void RenderTile(unsigned index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();

    private:
        Sprite* tileSet; // @TODO: fix this
        int rows;
        int columns;
        int tileWidth;
        int tileHeight;
};

#endif // TILESET_H