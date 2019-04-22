#include "Character.h"
#include <string>//strings
#include <vector>//vectors
#include <stdlib.h>//rand()
#include <iostream>//cin, cout FOR DEBUG, PLEASE REMOVE
#include "Global.h"
#include <time.h>

//Character player = *list.begin();

using namespace std;

//functions to set variables
void Character::set_name(string passed_name) {
    name = passed_name;
}
void Character::set_age(int passed_age) {
    age = passed_age;
}
void Character::set_height(int passed_height) {
    height = passed_height;
}
void Character::set_health(int passed_health) {//sets the absolute health
    status_data [2] = passed_health;
}
void Character::change_health(int passed_change) {//modifies the health
    status_data [2] += passed_change;
}

//functions to access every variable stored by class
string Character::get_name() {
    return name;
}
unsigned short Character::get_age() {
    return age;
}
unsigned short Character::get_height() {
    return height;
}
unsigned short Character::get_level() {
    return level;
}
unsigned short Character::get_gold() {
    return gold;
}
//array get functions
unsigned short Character::get_max_health() {
    return status_data[0];
}
unsigned short Character::get_health() {
    return status_data[1];
}
unsigned short Character::get_max_stamina() {
    return status_data[2];
}
unsigned short Character::get_stamina() {
    return status_data[3];
}
unsigned short Character::get_max_mana() {
    return status_data[4];
}
unsigned short Character::get_mana() {
    return status_data[5];
}
unsigned short Character::get_max_lust() {
    return status_data[6];
}
unsigned short Character::get_lust() {
    return status_data[7];
}
unsigned short Character::get_max_experience() {
    return status_data[8];
}
unsigned short Character::get_experience() {
    return status_data[9];
}
void Character::printCharacterInfo() {
    cout << "Name       : " << name << endl;
    cout << "Age        : " << age << endl;
    cout << "Height     : " << height << endl <<endl;
}
void Character::generate_full_random() {
    name = "random_name";//TODO replace with name randomly selected from names.txt or like
    age = rand() % (max_age-min_age) +  min_age; //generates age based upon user defined max_age and min_age - TODO allow ages to be weighted (50s still exist, but 80% spawns will be 20s)
    height = rand() % (max_height-min_height) + min_height;//TODO - base height upon averages as defined by disabled-world.com/calculators-charts/height-weight-teens.php
    for(int i=0; i<10; i++)
        status_data[i]=100;//TODO stats are based upon level/potentially class. higher level = more hp always, maybe not more mana/lust/stamina
    status_data [9] = 35;
    level = 1;//TODO for npcs set level = to Character? or base upon type of enemy spawning
    gold = 0;
}

//implementations

//Character constructors allow you to create a new Character completely randomly, or give certain information and leave the rest to generation. you can create a Character with only looks, stats, or using a predefined template.
//note max stats are calculated based upon passed
//default constructor
Character::Character() {
    name = "DEFAULT";
    age = 50;
    height = 78;
}
Character::Character(int passed_name, int passed_age, int passed_height) {
    name = passed_name;
    age = passed_age;
    height = passed_height;
}
Character::Character(string random_type) {
    //generate a Character based on a template defined by random_type
    if(!random_type.compare("debug")) {
        name = "debug";
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
