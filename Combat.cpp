#include "Combat.h"
#include "Global.h"
#include "curses/curses.h"
#include "Drawer.h"
#include "SceneController.h"


void Combat::main() {
    //Character *target = &characters[enemy_id];
    //drawer.screen_print("Combat status: "+to_string(g_in_combat));//g_mode_debug
    while(true){
        player_turn();
        if(target->get_health()<=0)
            victory();
        else if(characters[0].get_health()<=0)
            defeat();
        enemy_turn();
        if(target->get_health()<=0)
            victory();
        else if(characters[0].get_health()<=0)
            defeat();
    }
}
void Combat::player_turn() {
    int player_damage=rand() % 2 + 1;//default fist damage
    int weapon_skill = 12;//set weapon skill to unarmed for experience gain/checks
    /*TODO - re-add weapon damage
    if(characters[0].has_equipment[0]){//if player has weapon, change damage
        Item &player_weapon = *characters[0].inventory[0];
        player_damage=player_weapon.get_total_damage();
        if(!player_weapon.get_weapon_type().compare("sword")||!player_weapon.get_weapon_type().compare("dagger")){
            weapon_skill = 9;//set weapon skill to one handed
        }
    }
    */
    bool flag=0;
    int ch;
    while(!flag) {
        drawer.update();
        //what the combat options should look like eventually
        //string options[] = {"Inventory","","","Inspect","Attack","Spells","Specials","Taunt","Run","","",""};
        string options[] = {"","","","","Attack","","","","","","",""};
        drawer.options_print(options);

        //TODO - relocate to drawer.prompt() ?
        move(17,13);
        ch = getch();
        mvprintw(17,13,">");

        int hit_chance=0;
        int dodge_chance=0;

        switch (ch) {
            case 97://a
            case 65://A
                drawer.line_print("KEY_A              ");
                hit_chance = 50+10*characters[0].get_skill_level(weapon_skill);//hit chance starts at 50%, increases by 10% for each skill level. Proficient characters have 100% hit chance
                dodge_chance = 10*(((target->get_dex())-10)/2);//the dodge chance is equal to characters dex bonus(10-11>0,12-13>1,14-15>2) times 10
                if((rand()%100+1)>hit_chance-dodge_chance){
                    drawer.screen_print("You missed!");
                    drawer.screen_print(" ");
                }
                else{
                characters[0].change_skill_experience(weapon_skill,10);
                target->set_health(target->get_health()-player_damage);//TODO - should be decreased by player.get_attack_damage(), which is recalculated every time a new item is equiped, or combat is started
                drawer.screen_print("You deal "+to_string(player_damage)+" damage to "+target->get_name()+"!");
                drawer.screen_print(" ");
                flag=1;
                }
                break;
            case 115://s
            case 83://S
                drawer.line_print("KEY_S              ");
                break;
            case 113://q
            case 81://Q
                drawer.line_print("KEY_Q              ");
                break;
            case 102://f
            case 70: { //F
                drawer.line_print("KEY_F              ");
                break;
                case 114:
                case (int)'R':
                    drawer.line_print("KEY_R              ");
                    drawer.inspect_character(enemy_id);
                    drawer.screen_print(" ");
                    break;
                }
                break;
            default:
                drawer.line_print("INVALID INPUT      ");
                break;
        }
        if(target->get_health()>60000) {
            target->set_health(0);
        }
        drawer.target_status(enemy_id);//dont want to bloat update()
        if(target->get_health()<=0) {
            victory();
        }
    }
}
void Combat::enemy_turn() {
    int enemy_damage=rand() % 2 + 1;//default fist damage
    /*TODO - re-add weapon damage
    if(target->has_equipment[0]){//if target has weapon, change damage
        Item &target_weapon = *target[0].inventory[0];
        enemy_damage=target_weapon.get_total_damage();
    }
    */
    characters[0].set_health(characters[0].get_health()-enemy_damage);//TODO - replace with damage based upon enemy
    drawer.screen_print(target->get_name()+" deals "+to_string(enemy_damage)+" damage to you!");
    drawer.screen_print(" ");
    if(characters[0].get_health()>60000) {
        characters[0].set_health(0);
    }
    //switch (target->get_ai){}
}
void Combat::victory() {
    //Character *target = &characters[enemy_id];

    target->set_health(target->get_max_health());//g_mode_debug - target is given full health, not moved from location
    //TODO - remove character from map when killed
    //target->move_to_map(-1);//dead
    //mapper.maps.at(map_id).tiles[characters[0].get_map_y()][characters[0].get_map_x()]->characters_here.at(i)//remove character
    //drawer.clear_buffer();//delete all text that was previously displayed for combat
    drawer.screen_print("You have defeated "+target->get_name()+"!");
    drawer.screen_print(" ");
    /*OLD REMOVE experience on victory
    characters[0].set_experience(characters[0].get_experience()+target->get_level()*10);
    drawer.screen_print(" ");
    drawer.screen_print("You have gained "+to_string(target->get_level()*10)+" experience!");
    drawer.screen_print(" ");
    if(characters[0].get_experience()>characters[0].get_max_experience()) {
        characters[0].level_up();//level up handled by character
        drawer.screen_print("You have reached level "+to_string(characters[0].get_level())+"!");
        drawer.screen_print(" ");
    }
    */
    /*TODO - re-add loot system on victory
    shared_ptr<Armor> loot_armor = make_shared<Armor>(0);
    characters[0].inventory.push_back(loot_armor);
    drawer.screen_print(target->get_name()+ " dropped "+&loot_armor->get_material()[0]+" "+&loot_armor->get_armor_type()[0]+"!");
    drawer.screen_print(" ");
    */

    drawer.screen_print("Press any button to continue...");
    drawer.screen_print(" ");
    drawer.clear_options();
    drawer.update();
    move(17,13);
    getch();
    //mapper.maps.at(0).tiles[4][4]->remove_character(0);
    g_in_combat=0;
    controller.movement();
}
void Combat::defeat() {//TODO - flush out effects of loss
    drawer.clear_buffer();//delete all text that was previously displayed for combat
    drawer.screen_print("You have been defeated by "+target->get_name()+"!");
    drawer.screen_print(" ");
    drawer.screen_print("Press any button to continue...");
    drawer.update();
    move(17,13);
    getch();
    characters[0].set_health(characters[0].get_max_health());
    drawer.update();
    g_in_combat=0;
    controller.movement();

}
Combat::Combat(int passed_id,int encounter_type) {
    target = &characters[passed_id];
    enemy_id = passed_id;
    g_in_combat=true;
    drawer.clear_buffer();
    drawer.target_status(enemy_id);
    if(encounter_type==-1)//g_mode_debug fight
        drawer.screen_print("You have forced "+target->get_name()+" to fight you!");
    if(encounter_type==0)//basic ambush
        drawer.screen_print("You have been ambushed by the "+target->get_race()+" "+target->get_display_class()+", "+target->get_name()+"!");
    drawer.screen_print(" ");
    //drawer.inspect_character(enemy_id);
    main();
}

Combat::~Combat() {
    //dtor
}
