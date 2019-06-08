#include "Character.h"
#include "Global.h"

//SKILL FUNCTIONS
//get skill level
int Character::get_skill_level(string skill) {
    for(int i=0; i<25; i++)
        if(!skill.compare(g_names_skills[i]))
            return skill_level[i];
    return 999;//if theres an error, return 999;
}
int Character::get_skill_level(int skill_index) {
    return skill_level[skill_index];
}
//get skill experience
int Character::get_skill_experience(string skill) {
    for(int i=0; i<25; i++)
        if(!skill.compare(g_names_skills[i]))
            return skill_experience[i];
    return 999;//if theres an error, return 999;
}
int Character::get_skill_experience(int skill_index) {
    return skill_experience[skill_index];
}
//set skill level absolutely
void Character::set_skill_level(string skill,int value) {
    for(int i=0; i<25; i++)
        if(!skill.compare(g_names_skills[i]))
            skill_level[i]=value;
}
void Character::set_skill_level(int skill_index,int value) {
    skill_level[skill_index]=value;
}
//set skill experience absolutely
void Character::set_skill_experience(string skill, int value) {

    for(int i=0; i<25; i++)
        if(!skill.compare(g_names_skills[i]))
            skill_experience[i]=value;
}
void Character::set_skill_experience(int skill_index, int value) {
    skill_experience[skill_index]=value;
}
//set skill experience relative
void Character::change_skill_experience(string skill, int value) {
    for(int i=0; i<25; i++)
        if(!skill.compare(g_names_skills[i])) {
            skill_experience[i]+=value;
            check_skill(i);
        }
}
void Character::change_skill_experience(int skill_index, int value) {
    skill_experience[skill_index]+=value;
    check_skill(skill_index);
}
//check to see if skill level increased
void Character::check_skill(int skill_index) {
    if(skill_experience[skill_index]>=(skill_level[skill_index]+1)*100) { //if the experience is greater than or equal to experience needed for level
        skill_experience[skill_index]=((skill_level[skill_index]+1)*100)-skill_experience[skill_index];//carry over extra experience
        skill_level[skill_index]+=1;//increase level
        check_skill(skill_index);//call self as check for multiple level increases
        set_experience(get_experience()+10*skill_level[skill_index]);//increase players level experience, TODO - change based upon skills relation to class
    }
}


//ABILITY FUNCTIONS
void Character::set_str(int passed_str) {abilities[0]=passed_str;}
void Character::set_dex(int passed_dex) {abilities[1]=passed_dex;}
void Character::set_con(int passed_con) {abilities[2]=passed_con;}
void Character::set_int(int passed_int) {abilities[3]=passed_int;}
void Character::set_wis(int passed_wis) {abilities[4]=passed_wis;}
void Character::set_cha(int passed_cha) {abilities[5]=passed_cha;}
unsigned short Character::get_str() {return abilities[0];}
unsigned short Character::get_dex() {return abilities[1];}
unsigned short Character::get_con() {return abilities[2];}
unsigned short Character::get_int() {return abilities[3];}
unsigned short Character::get_wis() {return abilities[4];}
unsigned short Character::get_cha() {return abilities[5];}


//SIZE FUNCTIONS TODO - complete set functions
void Character::set_hair_length() { }
void Character::set_breast_size(int passed_breast_size) {size_data[1]=passed_breast_size;}
void Character::set_butt_size() {}
void Character::set_waist_size() {}
void Character::set_hips_size() {}
void Character::set_lips_size() {}
void Character::set_penis_size(int passed_penis_size) {size_data[6]=passed_penis_size;}
void Character::set_penis_girth() {}
void Character::set_balls_size() {}
void Character::set_nipple_size(int passed_nipple_size) {size_data[9] = passed_nipple_size;}
void Character::set_areola_size(int passed_areola_size) {size_data[10] = passed_areola_size;}
unsigned short Character::get_hair_length() {return size_data[0];}
unsigned short Character::get_breast_size() {return size_data[1];}
unsigned short Character::get_butt_size() {return size_data[2];}
unsigned short Character::get_waist_size() {return size_data[3];}
unsigned short Character::get_hips_size() {return size_data[4];}
unsigned short Character::get_lips_size() {return size_data[5];}
unsigned short Character::get_penis_size() {return size_data[6];}
unsigned short Character::get_penis_girth() {return size_data[7];}
unsigned short Character::get_balls_size() {return size_data[8];}
unsigned short Character::get_nipples_size() {return size_data[9];}
unsigned short Character::get_areolae_size() {return size_data[10];}


//STATUS FUNCTIONS TODO - complete set functions
void Character::set_health(int passed_health) {status_data [1] = passed_health;}//sets the absolute health
void Character::set_experience(int passed_experience) {status_data [9] = passed_experience;}
void Character::change_health(int passed_change) {status_data [1] += passed_change;}//modifies the health
unsigned short Character::get_max_health() {return status_data[0];}
unsigned short Character::get_health() {return status_data[1];}
unsigned short Character::get_max_stamina() {return status_data[2];}
unsigned short Character::get_stamina() {return status_data[3];}
unsigned short Character::get_max_mana() {return status_data[4];}
unsigned short Character::get_mana() {return status_data[5];}
unsigned short Character::get_max_lust() {return status_data[6];}
unsigned short Character::get_lust() {return status_data[7];}
unsigned short Character::get_max_experience() {return status_data[8];}
unsigned short Character::get_experience() {return status_data[9];}


//COLOR FUNCTIONS
void Character::set_skin_color(int passed_color) {color[0]=passed_color;}
void Character::set_hair_color(int passed_color) {color[1]=passed_color;}
void Character::set_eye_color (int passed_color) {color[2]=passed_color;}
unsigned short Character::get_skin_color() {return color[0];}
unsigned short Character::get_hair_color() {return color[1];}
unsigned short Character::get_eye_color () {return color[2];}


//MISC FUNCTIONS
void Character::level_up() {
    //TODO - add more depth to leveling up
    status_data[0] += rand() % 10;//increase the health by a hit die
    level+=1;
    status_data[8]=level*100;
    status_data[9]=0;
}
void Character::update_stats() {
    armor_rating=0;
    /*TODO - re-add armor rating system
    if(has_equipment[1]!=0)//if character has helmet
        armor_rating+=.4*equipment[1]->get_armor_rating();
    if(has_equipment[2]==1)//chest
        armor_rating+=.15*equipment[2]->get_armor_rating();
    if(has_equipment[3]!=0)//legs
        armor_rating+=.15*equipment[3]->get_armor_rating();
    if(has_equipment[4]!=0)//boots
        armor_rating+=.15*equipment[4]->get_armor_rating();
    */
}
//void Character::add_item(string passed_item){inventory.emplace_back(passed_item,"base.material.generic","",0,{"base.enchantment.fortify_health","base.enchantment.fortify_mana"});}
/*
void Character::equip_item(string passed_item){
    int slot = moduleHandler.get_equipment_type(passed_item);
    if(slot!=-1){
        if(equipment[slot].compare(""))
            equipment[slot]=passed_item;
        else{
            inventory.push_back(equipment[slot]);
            equipment[slot]=passed_item;
        }
    }
}
*/
//misc set
void Character::set_name(string passed_name) {name = passed_name;}
void Character::set_age(int passed_age) {age = passed_age;}
void Character::set_height(int passed_height) {height = passed_height;}
void Character::set_race(string temp_race) {race = temp_race;}
void Character::move_to(int passed_y,int passed_x) {
    map_y=passed_y;
    map_x=passed_x;
}
void Character::move_to_map(int passed_map_id) {current_map=passed_map_id;}
//misc get
string Character::get_name() {return name;}
unsigned short Character::get_age() {return age;}
unsigned short Character::get_height() {return height;}
unsigned short Character::get_level() {return level;}
unsigned short Character::get_gold() {return gold;}
unsigned short Character::get_map() {return current_map;}
unsigned short Character::get_armor_rating() {return armor_rating;}
short Character::get_masculinity() {return masculinity;}
int Character::get_map_x() {return map_x;}
int Character::get_map_y() {return map_y;}
string Character::get_display_class() {return display_class;}
string Character::get_race() {return race;}


//verbose character generator
void Character::generate_full_random() {
    //ensure randoms are random
    time_t temp;
    srand((unsigned) time(&temp));

    //all characters are currently human fighters
    race = "human";
    display_class = "fighter";//display_class only truly has meaning for enemies, players are much more flexible
    is_generic_race = false;//all humans are unique, bears are not

    set_str(rand()%4+10);
    set_dex(rand()%4+10);
    set_con(rand()%4+8);
    set_int(rand()%2+7);
    set_wis(rand()%2+8);
    set_cha(rand()%2+8);

    //set character stats
    level = 1;//TODO for npcs set level = to Character? or base upon type of enemy spawning
    for(int i=0; i<10; i++)
        status_data[i]=100;//TODO stats are based upon level/potentially class. higher level = more hp always, maybe not more mana/lust/stamina
    status_data[0] = 10;//TODO - max health is based upon 1d10 hit die for now, maybe not later
    for(int i = 2; i<=level; i++)//for ever character level past 1
        status_data[0] += rand() % 10;//increase the health by a hit die
    status_data[1] = status_data[0];//health starts at max
    status_data [9] = status_data [7] = 0;//exp,lust always start at 0
    status_data [3] = 45;
    armor_rating = 0;
    gold = 0;

    //set character location
    current_map = 0;//set to no map
    map_x = 0;
    map_y = 0;

    if(!g_mode_shota) {
        age = rand() % (g_age_max-g_age_min) +  g_age_min; //generates age based upon user defined g_age_max and g_age_min - TODO allow ages to be weighted (50s still exist, but 80% spawns will be 20s)
        //select sex, set masculinity
        switch(rand() % 2) {
        case 0:
            name = g_names_archaic_male[rand() % (271)];//TODO - replace 271 with length of array
            has_penis=true;
            has_vagina=false;
            set_penis_size(rand() % 10+1);
            masculinity=rand() % 51;
            break;
        case 1:
            name = g_names_archaic_female[rand() % (153)];
            has_penis=false;
            has_vagina=true;
            masculinity=(-1)*(rand() % 51);
            break;
        }
        //dont let traps get too old it ruins the fun
        if(masculinity<=10&&has_penis&&get_age()>25)
            age = rand() % (25-g_age_min) +  g_age_min;

        //set stats for males
        if(masculinity>10) {
            set_breast_size(0);
            switch(age) {
            case 12:
                height=rand() % 12 + 53;
                break;
            case 13:
                height=rand() % 12 + 55;
                break;
            case 14:
                height=rand() % 13 + 58;
                break;
            case 15:
                height=rand() % 13 + 61;
                break;
            case 16:
                height=rand() % 14 + 62;
                break;
            case 17:
                height=rand() % 14 + 63;
                break;
            default:
                height=rand() % 14 + 64;
                break;
            }
        }
        //set stats for females/traps
        else {
            switch(age) {
            case 12:
                set_breast_size(rand() % 350);
                height=rand() % 12 + 53;
                break;
            case 13:
                set_breast_size(rand() % 450);
                height=rand() % 12 + 56;
                break;
            case 14:
            case 15:
                set_breast_size(rand() % 550);
                height=rand() % 13 + 57;
                break;
            case 16:
                set_breast_size(rand() % 600);
                height=rand() % 13 + 57;
                break;
            case 17:
            case 18:
                set_breast_size(rand() % 700);
                height=rand() % 13 + 57;
            case 19:
            case 20:
            default:
                set_breast_size(rand() % 1000);
                height=rand() % 13 + 58;
                break;
            }
            if(has_penis)
                set_breast_size(rand() % 400);
        }
        switch(get_breast_size()/100) {
        case 0://flat
            set_nipple_size(rand() % 2 + 1);
            set_areola_size(rand() % 9);
            break;
        case 1://AAA
            set_nipple_size(rand() % 3 + 1);
            set_areola_size(rand() % 9);
            break;
        case 2://AA
            set_nipple_size(rand() % 3 + 1);
            set_areola_size(rand() % 9);
            break;
        case 3://A
            set_nipple_size(rand() % 4 + 1);
            set_areola_size(rand() % 15);
            break;
        case 4://B
            set_nipple_size(rand() % 5 + 1);
            set_areola_size(rand() % 20);
            break;
        case 5://C
            set_nipple_size(rand() % 6 + 1);
            set_areola_size(rand() % 25);
        case 6://D
            set_nipple_size(rand() % 7 + 2);
            set_areola_size(rand() % 30);

            break;
        case 8://E
            set_nipple_size(rand() % 8 + 2);
            set_areola_size(rand() % 35);
            break;
        case 10://F
        case 11:
            set_nipple_size(rand() % 9 + 2);
            set_areola_size(rand() % 40);
            break;
        default:
            set_nipple_size(rand() % 10 + 2);
            set_areola_size(rand() % 45);
            break;
        }
    }

    else { //shota mode, hasn't been updated in awhile :)
        switch(rand() % 2) {
        case 0:
            age=12;
            set_breast_size(0);
            set_penis_size(3);
            has_penis=true;
            has_vagina=false;
            height=rand() % 12 + 53;
            masculinity=rand() % 29;
            break;
        case 1:
            age=rand() % 30 +  25;
            set_breast_size(rand() % 4 + 6);
            has_penis=false;
            has_vagina=true;
            height=rand() % 14 + 68;
            masculinity=(-1)*(rand() % 10 + 40);
            break;
        }
    }

    //set hair color
    color[2]=rand() % 9; //0-8

    //set eye color
    color[1]=rand() % 6; //0-5

    //set skin color
    color[0]=rand() % 12;//0-11
}


//implementations
Character::Character() {
    equipment.resize(6);
    generate_full_random();
}
Character::Character(string random_type) {
    equipment.resize(6);
    //generate a Character based on a template defined by random_type
    if(!random_type.compare("g_mode_debug")) {
        name = "g_mode_debug";
        age = 999;
        height = 120;
    } else if(!random_type.compare("random")) {
        generate_full_random();
    } else {
        name = "no_type_specified";
        age = 0;
        height = 0;
    }
}
