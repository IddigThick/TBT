#include "Maper.h"
#include "curses/curses.h"

void Maper::print(int map_id){
    for(int y=19;y<25;y++)
        for(int x=0;x<6;x++)
            mvprintw(y,x*2,"%c",maps[0][y-19][x]->tile_symbol);
}


Maper::Maper()
{
    Character *player = &characters[0];
    //add 1 debug map to maps vector at position 0
    Map *m;
    m = new Map();
    maps.push_back(*m);
}

Maper::~Maper()
{
    //dtor
}
