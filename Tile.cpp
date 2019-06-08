#include "Tile.h"
#include <string>

void Tile::add_character(int character_id){
    characters_here.push_back(character_id);
}
Tile::Tile(int passed_tile_type)
{
    tile_type=passed_tile_type;
    switch (tile_type)
    {
        case 0:
            tile_name.assign("error");
            tile_accessible=true;
            tile_symbol='?';
            break;
        case 1:
            tile_name.assign("road");
            tile_accessible=true;
            tile_symbol='O';
            break;
        case 2:
            tile_name.assign("forest");
            tile_accessible=true;
            tile_symbol='#';
            break;
        case 3:
            tile_name.assign("mountain");
            tile_accessible=false;
            tile_symbol='X';
            break;
        default:
            tile_name.assign("error");
            tile_accessible=true;
            tile_symbol='?';
            break;
    }
}

Tile::~Tile()
{
    //dtor
}
