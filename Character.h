#ifndef CHARACTER_H
#define CHARACTER_H
//used in header
#include <string>//strings
#include <vector>//vectors
#include <memory>//smart vector
#include "Structures.h"

//used in source
#include <string>//strings
#include <vector>//vectors
#include <stdlib.h>//rand()
#include <array>//size()
#include <time.h>
#include "curses/curses.h"


using namespace std;

class Character {
  public:
    //CONSTRUCTORS
    Character();//default > generate a completely random Character
    Character(string);//generate a Character based upon preset as defined by string
    virtual ~Character() {}

    //PUBLIC VARIABLES
    bool has_equipment[6] = {0,0,0,0,0,0};
    //vector<string> inventory;
    //vector<string> equipment;

    vector<Item> inventory;
    vector<Item> equipment;
    /*OLD inventory system
    vector<shared_ptr<Item>> inventory;
    vector<shared_ptr<Item>> equipment;
    */
    bool has_vagina;
    bool has_penis;
    bool is_anal_virgin;
    bool is_oral_virgin;
    bool is_vaginal_virgin;
    bool is_penile_virgin;
    string race;
    bool is_generic_race;
    string display_class;


    //SKILL FUNCTIONS
    int skill_experience[25] = {};
    int skill_level[25] = {};
    //skill functions
    int get_skill_level(string skill);
    int get_skill_level(int skill_index);
    int get_skill_experience(string skill);
    int get_skill_experience(int skill_index);
    //set skill level absolutely
    void set_skill_level(string skill,int value);
    void set_skill_level(int skill_index,int value);
    //set skill experience absolutely
    void set_skill_experience(string skill,int value);
    void set_skill_experience(int skill_index,int value);
    //set skill experience relative
    void change_skill_experience(string skill,int value);
    void change_skill_experience(int skill_index,int value);
    //check to see if skill level increased
    void check_skill(int skill_index);


    //ABILITY FUNCTIONS
    unsigned short abilities [6] = {0,0,0,0,0,0};//STR/DEX/CON/INT/WIS/CHA, default ability values should AlWAYS be overwritten in char gen
    //set functions
    void set_str(int passed_str);
    void set_dex(int passed_dex);
    void set_con(int passed_con);
    void set_int(int passed_int);
    void set_wis(int passed_wis);
    void set_cha(int passed_cha);
    //get functions
    unsigned short get_str();
    unsigned short get_dex();
    unsigned short get_con();
    unsigned short get_int();
    unsigned short get_wis();
    unsigned short get_cha();


    //SIZE FUNCTIONS
    //set functions
    void set_hair_length();
    void set_breast_size(int passed_breast_size);
    void set_butt_size();
    void set_waist_size();
    void set_hips_size();
    void set_lips_size();
    void set_penis_size(int passed_penis_size);
    void set_penis_girth();
    void set_balls_size();
    void set_nipple_size(int passed_nipple_size);
    void set_areola_size(int passed_areola_size);
    //get functions
    unsigned short get_hair_length();
    unsigned short get_breast_size();
    unsigned short get_butt_size();
    unsigned short get_waist_size();
    unsigned short get_hips_size();
    unsigned short get_lips_size();
    unsigned short get_penis_size();
    unsigned short get_penis_girth();
    unsigned short get_balls_size();
    unsigned short get_nipples_size();
    unsigned short get_areolae_size();


    //STATUS FUNCTIONS
    //set functions
    void set_health(int passed_health);
    void set_experience(int passed_experience);
    void change_health(int passed_change);
    //get functions
    unsigned short get_max_health();
    unsigned short get_health();
    unsigned short get_max_stamina();
    unsigned short get_stamina();
    unsigned short get_max_mana();
    unsigned short get_mana();
    unsigned short get_max_lust();
    unsigned short get_lust();
    unsigned short get_max_experience();
    unsigned short get_experience();

    //COLOR FUNCTIONS
    //set functions
    void set_hair_color(int passed_color);
    void set_eye_color(int passed_color);
    void set_skin_color(int passed_color);
    //get functions
    unsigned short get_hair_color();
    unsigned short get_eye_color();
    unsigned short get_skin_color();


    //MISC FUNCTIONS
    void level_up();
    void update_stats();
    void add_item(string passed_item);
    void equip_item(string passed_item);
    //set functions
    void set_name(string passed_name);
    void set_age(int passed_age);
    void set_height(int passed_height);
    void set_race(string temp_race);
    void move_to(int passed_y,int passed_x);
    void move_to_map(int passed_map_id);
    //get functions
    string get_name();
    unsigned short get_age();
    unsigned short get_height();
    unsigned short get_level();
    unsigned short get_gold();
    unsigned short get_map();
    unsigned short get_armor_rating();
    string get_display_class();
    string get_race();
    short get_masculinity();
    int get_map_x();//use for player only?
    int get_map_y();//use for player only?



    //PRIVATE VARIABLES
    //collection of items, where items can by any derivative of Item


  private:
    string name;
    short masculinity;

    //TODO - consider adding to array
    unsigned short age;
    unsigned short height;
    unsigned short weight;

    //TODO - consider adding to array location_data
    unsigned short current_map;
    unsigned short map_x;
    unsigned short map_y;

    unsigned short status_data [10];//max_health,health,max_stamina,stamina,max_mana,mana,max_lust,lust,max_experience,experience

    //TODO - consider adding to status_data
    unsigned short level;
    unsigned short corruption;
    unsigned short gold;
    unsigned short armor_rating;


    unsigned short size_data [11];
    /*hair,breast,butt,waist,hips,lips,penis length,penis girth,ball,nipple,areola
      hair - inches
      breast - 0-10 - FLAT,AAA,AA,A,B,C,D,E,F,G,H
      butt - 0-7 - flat,small,plump,bubble,huge,enormus,gigantic,absurd
      waist - 0-5 - very narrow,
      hips - 0-5 - very narrow,narrow,wide,very wide,inhumanly wide,absurd
      penis length - inches
      penis girth - inches
      balls - diameter
      nipple length - 0-40 - tiny, 3small, 5large, 10big
      areola - 0-60 - tiny, 10small, 20medium-sized, 30large, 40huge, 50giant
    */

    unsigned short color[3] = { 0 };//skin_color, hair_color, eye_color

    //TODO - add names_nipple_shapes?

    void generate_full_random();
};

#endif // CHARACTER_H
