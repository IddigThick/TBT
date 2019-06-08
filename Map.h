#ifndef MAP_H
#define MAP_H
#include "Tile.h"

class Map
{
    public:
        Map();
        virtual ~Map();
        Tile* tiles[6][6];

    protected:
        get_map_type();//interior/exterior/area
        get_map_biome();//icy,temperate,desert,corrupted > only applies to exterior?
    private:
};

#endif // MAP_H
