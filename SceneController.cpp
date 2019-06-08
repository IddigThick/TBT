#include "SceneController.h"
#include <string>
#include "Global.h"
#include "curses/curses.h"
#include "Combat.h"
#include "time.h"
#include "Character.h"
#include <vector>

int SceneController::get_input(){
    int ch;
    keypad(stdscr, TRUE);
    drawer.clear_line();
    move(17,13);
    ch = getch();
    //printw(">");
    //mvprintw(17,13,">");
    if(g_mode_debug){
        switch (ch){
        case KEY_LEFT:
            drawer.line_print("KEY_LEFT");
            break;
        case KEY_RIGHT:
            drawer.line_print("KEY_RIGHT");
            break;
        case KEY_UP:
            drawer.line_print("KEY_UP");
            break;
        case KEY_DOWN:
            drawer.line_print("KEY_DOWN");
            break;
        case 97://a
        case 65://A
            drawer.line_print("KEY_A");
            break;
        case 115://s
        case 83://S
            drawer.line_print("KEY_S");
            break;
        case 113://q
        case 81://Q
            drawer.line_print("KEY_Q");
            break;
        case 102://f
        case 70://F
            drawer.line_print("KEY_F");
            break;
        case (int)'`':
            drawer.line_print("KEY_`");
            break;
        case 27://escape
            drawer.line_print("KEY_ESC");
            break;
        default:
            drawer.line_print("INVALID INPUT      ");
            break;
        }
    }
    return ch;
}
void SceneController::movement(){
    clear();
    drawer.clear_screen();
    drawer.init();
    string options[] = {"Inventory","","","","Character","","","","","","",""};
    drawer.options_print(options);
    characters[0].move_to_map(0);
    mapper.print(characters[0].get_map());
    int rows =  sizeof mapper.maps.at(characters[0].get_map()).tiles / sizeof mapper.maps.at(characters[0].get_map()).tiles[0];
    int cols = sizeof mapper.maps.at(characters[0].get_map()).tiles[0] / sizeof(int);
    while(true){
        switch (get_input()){
            case KEY_LEFT:
                if(characters[0].get_map_x()>0){
                    characters[0].move_to(characters[0].get_map_y(),characters[0].get_map_x()-1);
                    encounter();
                }
                break;
            case KEY_RIGHT:
                if(characters[0].get_map_x()<cols-1){
                    characters[0].move_to(characters[0].get_map_y(),characters[0].get_map_x()+1);
                    encounter();
                }
                break;
            case KEY_UP:
                if(characters[0].get_map_y()>0){
                    characters[0].move_to(characters[0].get_map_y()-1,characters[0].get_map_x());
                    encounter();
                }
                break;
            case KEY_DOWN:
                if(characters[0].get_map_y()<rows-1){
                    characters[0].move_to(characters[0].get_map_y()+1,characters[0].get_map_x());
                    encounter();
                }
                break;
            case 97://a
            case 65://A
                inspect_character(0);
                break;
            case 113://q
            case 81://Q
                inventory();
                break;
            case (int)'`':
                if(g_mode_debug)
                    g_mode_debug_menu();
                break;
            case 27://escape
                clear();
                menu.main();
                break;
        }
        mapper.print(characters[0].get_map());
    }
}
void SceneController::encounter(){
    mapper.print(characters[0].get_map());
    if(!mapper.maps.at(characters[0].get_map()).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->tile_name.compare("forest")){//if player moves onto a forest tile
        if(rand() % 100>80){
            drawer.line_print("You encounter an enemy!");
            characters.emplace_back("random");
            //characters.end()->set_name("Thief");
            Combat combat_start(characters.size()-1,0);
        }
    }
}
void SceneController::inventory(){
    string options[] = {"Equipment","","","","Equip","Inspect","","","Back","","",""};
    drawer.options_print(options);
    drawer.inventory_print(0);
    while(true){
        switch (get_input()){
            case 97://a
            case 65://A
                drawer.line_print("                    ");
                move(17,14);
                /*OLD equip item
                getstr(str);
                equip_item(atoi(str)-1);
                */
                break;
            case 115://s
            case 83://S
                drawer.line_print("                    ");
                move(17,14);
                drawer.inventory_print(0);
                drawer.options_print(options);
                break;
            case 113://q
            case 81://Q
                drawer.line_print("KEY_Q              ");
                equipment();
                break;
            case 90://z
            case 122://Z
                drawer.line_print("KEY_Z              ");
                movement();
                break;
            default:
                drawer.line_print("INVALID INPUT      ");
                break;
        }
    }
}
void SceneController::equipment(){
    string options[] = {"Inventory","","","","Unequip","Inspect","","","Back","","",""};
    drawer.options_print(options);
    drawer.clear_screen();
    drawer.equipment_print();
    while(true){
        switch (get_input()){
            case 97://a
            case 65://A
                /*OLD unequip item
                drawer.line_print("                    ");
                move(17,14);
                getstr(str);
                characters[0].inventory.push_back(characters[0].equipment.at(atoi(str)-1));
                characters[0].equipment.erase(characters[0].equipment.begin()+(atoi(str)-1));
                characters[0].has_equipment[atoi(str)-1]=0;
                drawer.equipment_print();
                break;
                */
            case 115://s
            case 83://S
                drawer.line_print("                    ");
                break;
            case 113://q
            case 81://Q
                drawer.line_print("KEY_Q              ");
                inventory();
                break;
            case 90://z
            case 122://Z
                drawer.line_print("KEY_Z              ");
                movement();
                break;
            default:
                drawer.line_print("INVALID INPUT      ");
                break;
        }
    }
}
/*OLD equip_item function for object items
void SceneController::equip_item(int selection){
    int type = -1;
    if(selection+1>characters[0].inventory.size()){//first check if selected item exists
        drawer.line_print("There is no item in slot "+to_string(selection+1));
        return;
    }
    else if(characters[0].inventory.at(selection)->get_item_type().compare("weapon")==0){//if the item selected is a weapon
        type=0;
        drawer.line_print("Weapon equipped");
    }
    else if(characters[0].inventory.at(selection)->get_item_type().compare("armor")==0){//if the item selected is armor
        if(characters[0].inventory.at(selection)->get_armor_type().compare("chest")==0){//if chest armor
            type=2;
            drawer.line_print("Chest armor equipped");
        }
        else if(characters[0].inventory.at(selection)->get_armor_type().compare("helmet")==0){//if chest armor
            type=1;
            drawer.line_print("Helmet equipped");
        }
        else if(characters[0].inventory.at(selection)->get_armor_type().compare("gauntlets")==0){//if chest armor
            type=3;
            drawer.line_print("Gauntlets equipped");
        }
        else if(characters[0].inventory.at(selection)->get_armor_type().compare("legs")==0){//if chest armor
            type=4;
            drawer.line_print("Legs equipped");
        }
        else if(characters[0].inventory.at(selection)->get_armor_type().compare("boots")==0){//if chest armor
            type=5;
            drawer.line_print("Boots equipped");
        }
    }

    if(type!=-1){//if an item that can be equiped has been selected
        if(characters[0].has_equipment[type]==1){//if player already has item in this slot
            characters[0].inventory.push_back(characters[0].equipment.at(type));
            characters[0].equipment.at(type)=characters[0].inventory.at(selection);
            characters[0].inventory.erase(characters[0].inventory.begin()+selection);
            characters[0].has_equipment[type]=1;
            drawer.inventory_print();
        }
        else{//if player has no item in this slot
            characters[0].equipment.at(type)=characters[0].inventory.at(selection);
            characters[0].inventory.erase(characters[0].inventory.begin()+selection);
            characters[0].has_equipment[type]=1;
            drawer.inventory_print();
        }
    }
    else{//if the type is not equipable
        drawer.line_print("You can not equip this item"+characters[0].inventory.at(selection)->get_item_type()+characters[0].inventory.at(selection)->get_armor_type());
        return;
    }
    characters[0].update_stats();
}
*/

void SceneController::inspect_item(int prev, int selection){//0 player inventory, 1 ground
    string options[] = {"","","","","","","","","Back","","",""};
    drawer.options_print(options);
    drawer.clear_buffer();
    drawer.clear_screen();

    /*OLD inspect item function
    if(selection+1>characters[0].inventory.size()){//first check if selected item exists
        drawer.line_print("There is no item in slot "+to_string(selection+1));
        return;
    }
    if(prev==0){
        drawer.inspect_item(*characters[0].inventory[selection]);
    }
    */

    int ch;
    while(true){
        move(17,14);
        ch = getch();
        if(ch == 90 ||ch == 122)//check for z||Z press
        {
            drawer.line_print("KEY_Z              ");
            return;
        }
        else{
            drawer.line_print("INVALID INPUT      ");
        }
    }
}
void SceneController::inspect_character(int passed_id){
    string options[] = {"","","","","Skills","","","","Back","","",""};
    drawer.options_print(options);
    drawer.clear_buffer();
    drawer.clear_screen();
    characters[passed_id].update_stats();
    drawer.inspect_character(passed_id);
    int ch;
    while(true){
        move(17,14);
        ch = getch();
        if(ch == 65 || ch==97)
        {
            drawer.line_print("KEY_A              ");
            inspect_character_skills(0);
        }
        else if(ch == 90 ||ch == 122)//check for z||Z press
        {
            drawer.line_print("KEY_Z              ");
            movement();
        }
        else{
            drawer.line_print("INVALID INPUT      ");
        }
    }
}
void SceneController::inspect_character_skills(int passed_id){
    //string options[] = {"","","","","","","","","Back","","",""};
    //drawer.options_print(options);
    //drawer.clear_screen();
    clear();
    mvprintw(24,0,"z - back");
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    attron(COLOR_PAIR(1));
    mvprintw(0,0,"Skills                                                                          ");
    attroff(COLOR_PAIR(1));

    int adjust = 6;
    attron(COLOR_PAIR(1));
    mvprintw(2,6+adjust,"Major:");
    mvprintw(7,6+adjust,"Armor:");
    mvprintw(11,4+adjust,"Weapons:");
    mvprintw(15,6+adjust,"Magic:");
    mvprintw(22,3+adjust,"Crafting:");
    attroff(COLOR_PAIR(1));
//"Thieving","Spellcraft","Athletics","Survival","Perception","Heavy","Medium","Light","Unarmored","One-handed","Two-handed","Ranged","Unarmed","Abjuration","Conjuration","Divination","Enchantment","Evocation","Illusion","Necromancy","Transmutation","Alchemy","Armorsmith","Weaponsmith"
    int index=0;
    int shift = 2;
    for(int i=0; i<24 ; i++){
        mvprintw(i+shift,13+adjust,&g_names_skills[i][0]);
        mvprintw(i+shift,27+adjust,"%i",characters[passed_id].get_skill_level(i));
        mvprintw(i+shift,31+adjust,"(%i/%i)",characters[passed_id].get_skill_experience(i),(characters[passed_id].get_skill_level(i)+1)*100);
        mvprintw(i+shift,45+adjust,&g_names_skill_levels[characters[passed_id].get_skill_level(i)][0]);
    }
    refresh();
    int ch;
    while(true){
        move(17,14);
        ch = getch();
        if(ch == 90 ||ch == 122)//check for z||Z press
        {
            clear();
            drawer.init();
            drawer.update();
            inspect_character(0);
        }else if(ch==KEY_UP){
            if(index>0)
                index--;
        }else if(ch==KEY_DOWN){
            //if(index<
        }
    }
}
void SceneController::g_mode_debug_menu(){
    mvprintw(19,13," Q-WepGenTest W-           E-           R-          ");
    mvprintw(21,13," A-           S-           D-           F-ForceFight");
    mvprintw(23,13," Z-Back       X-           C-           V-CharGenTst");
    drawer.clear_buffer();
    drawer.screen_print("This is the g_mode_debug menu, options may break the game");
    drawer.screen_print(" ");
    drawer.screen_print("ForceFight-initiate combat, target = first character on player's tile");
    drawer.screen_print(" ");
    drawer.screen_print("CharGenTst-generate a random character and inspect them");
    drawer.screen_print(" ");
    drawer.screen_print("WepGenTest-generate a random weapon and print name");
    int ch;
    while(true){
        move(17,13);
        ch = getch();
        mvprintw(17,13,">");
        switch (ch){
            case KEY_LEFT:
                drawer.line_print("KEY_LEFT           ");
                break;
            case KEY_RIGHT:
                drawer.line_print("KEY_RIGHT          ");
                break;
            case KEY_UP:
                drawer.line_print("KEY_UP             ");
                break;
            case KEY_DOWN:
                drawer.line_print("KEY_DOWN           ");
                break;
            case 97://a
            case 65://A
                drawer.line_print("KEY_A              ");
                break;
            case 115://s
            case 83://S
                drawer.line_print("KEY_S              ");
                break;
            case 113://q
            case 81://Q
                drawer.line_print("KEY_Q              ");
                drawer.clear_screen();
            drawer.init();
                mvprintw(1,13,"1 ");
                refresh();
                time_t temp1;
                srand((unsigned) time(&temp1));
                PLAYER.inventory.push_back(moduleHandler.generate_random_weapon());
                drawer.clear_buffer();
                mvprintw(0,13,&moduleHandler.get_material_name(PLAYER.inventory.back().material_id)[0]);
                printw(" ");
                printw((moduleHandler.get_item_name(PLAYER.inventory.back().item_id)).c_str());
                PLAYER.inventory.erase(PLAYER.inventory.end());
                break;
            case 102://f
            case 70://F
                {
                drawer.line_print("KEY_F              ");
                if(mapper.maps.at(characters[0].get_map()).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->characters_here.size()>0)
                    Combat combat_start(mapper.maps.at(characters[0].get_map()).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->characters_here.at(0),-1);
                else
                    drawer.line_print("There is no character to fight here");
                break;
                }
                break;
            case 90:
            case 122:
                drawer.line_print("KEY_Z              ");
                movement();
                break;
            case (int)'v':
            case (int)'V':
                drawer.line_print("KEY_V              ");
                time_t temp;
            srand((unsigned) time(&temp));
                Character *f1;
                f1 = new Character("random");
                characters.emplace_back(*f1);
                drawer.clear_buffer();
                drawer.inspect_character(characters.size()-1);
                characters.erase(characters.end());
                break;
            default:
                drawer.line_print("INVALID INPUT      ");
                break;
        }
    }
}
//void combat_main(int passed_id){}
SceneController::SceneController()
{
    //ctor
}

SceneController::~SceneController()
{
    //dtor
}
