#include "Mapper.h"
#include "curses/curses.h"
#include "Global.h"
#include "Character.h"
#include <memory>//unique_ptr
//TODO - should be integrated into Drawer, no reason to be its own function


void Mapper::print(int map_id){//print tile info in right panel
    start_color();
    //loop through every tile, print symbol on map
    for(int y=19;y<25;y++)
        for(int x=0;x<6;x++){
            switch(maps.at(map_id).tiles[y-19][x]->tile_symbol){
                case '#' :
                    init_pair(1, COLOR_GREEN, COLOR_BLACK);
                    attron(COLOR_PAIR(1));
                    mvprintw(y,x*2,"#");
                    attroff(COLOR_PAIR(1));
                    break;
                case '?' :

                    init_pair(3, COLOR_RED, COLOR_BLACK);
                    attron(COLOR_PAIR(3));
                    mvprintw(y,x*2,"?");
                    attroff(COLOR_PAIR(3));
                    break;
                default :
                    mvprintw(y,x*2,"%c",maps.at(map_id).tiles[y-19][x]->tile_symbol);
            }
        }

    //print character
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(2));
    mvprintw((characters[0].get_map_y())+19,(characters[0].get_map_x())*2,"%c",'@');
	attroff(COLOR_PAIR(2));

    //print location
    //g_mode_debug - mapper prints location info itself, should be handled by drawer
    //mvprintw(0,13,"You are in a %s tile",&maps.at(map_id).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->tile_name[0]);
    //mvprintw(0,13,"                                                       ");
    //fixed to use drawer
    drawer.clear_buffer();
    drawer.screen_print("You are in a "+maps.at(map_id).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->tile_name+" tile");

    for(int i=0;i<24;i++){
        mvprintw(i,69,"           ");
    }
    mvprintw(0,69,"Characters:");
    for(unsigned short i=0;i<maps.at(map_id).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->characters_here.size();i++){
        mvprintw(i+1,69,"%s",characters[maps.at(map_id).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->characters_here.at(i)].get_name().c_str());
    }
    /*TODO - re-add item printing on map screen
    mvprintw(12,69,"Items:");
    //mvprintw(i+13,69,"%s",maps.at(0).tiles[3][3]->items.at(i)->get_name().c_str());
    for(unsigned short i=0;i<maps.at(map_id).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->items.size();i++){
        mvprintw(i+13,69,"%s",maps.at(map_id).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->items[i]->get_item_type().c_str());
        //mvprintw(i+13,69,"%s",maps.at(map_id).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->items[3]->item_name().c_str());
        //Weapon test = maps.at(map_id).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->items[i];
    }
    */
    refresh();
}
/*
void Mapper::g_mode_debug_add_item(){
    //maps.at(0).tiles[3][3]->items.emplace_back(new Item);
    int dmg1[] = {10,0,0,0,5};//damage to be stored in weapontest
    int dmg2[] = {20,0,0,0,0};
    char scale1[] = {'S','-','-','-','-','S'};//stat scaling to be stored
    char scale2[] = {'B','-','-','-','-','-'};
    Weapon weapontest(99,100,"golden",99,"Windslicer",999,"dagger",dmg1,dmg1,scale1,10,10,10,0,10);//weapon test (derivative of Equipable)
    Weapon weapontest2(23,100,"iron",99,"Old Faithful",1,"sword",dmg2,dmg2,scale2,2,2,2,2,2);//weapon test (derivative of Equipable)
    maps.at(0).tiles[4][4]->items.emplace_back(new Weapon(99,100,"golden",99,"Windslicer",999,"dagger",dmg1,dmg1,scale1,10,10,10,0,10));
    maps.at(0).tiles[4][4]->items.emplace_back(new Weapon(23,100,"iron",99,"Old Faithful",1,"sword",dmg2,dmg2,scale2,2,2,2,2,2));
}
*/
Mapper::Mapper()
{
    Map *m;
    m = new Map();
    maps.push_back(*m);
    //maps.at(0).tiles[4][4]->add_character(1);
}

Mapper::~Mapper()
{
    //dtor
}
