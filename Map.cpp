#include "Map.h"
#include "Tile.h"
#include <time.h>

Map::Map()
{
    Tile *t;
    //generate seed for rand
    time_t temp;
    srand((unsigned) time(&temp));
    //generate g_mode_debug map
    for(int y=0;y<6;y++)
        for(int x=0;x<6;x++){
            t = new Tile(rand() % 2 + 2);
            tiles[y][x] = t;
    }
}

Map::~Map()
{
    //dtor
}
