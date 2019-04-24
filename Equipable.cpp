#include "Equipable.h"
#include "Global.h"
#include "Item.h"
#include <string>//strings

using namespace std;

//functions to set variables
void Equipable::set_durability(unsigned short passed_durability){
    durability=passed_durability;
}
void Equipable::set_max_durability(unsigned short passed_durability){
    max_durability=passed_durability;
}
void Equipable::set_material(string passed_material){
    material=passed_material;
}
void Equipable::set_weight(unsigned short passed_weight){
    weight=passed_weight;
}

//functions to access variables stored by class
unsigned short Equipable::get_durability(){
    return durability;
}
unsigned short Equipable::get_max_durability(){
    return max_durability;
}
string Equipable::get_material(){
    return material;
}
unsigned short Equipable::get_weight(){
    return weight;
}

//implementations
Equipable::Equipable() {
    durability=100;
    max_durability=100;
    material = "DEFAULT MATERIAL";
    weight = 1;
}
Equipable::Equipable(int passed_durability, int passed_max_durability, string passed_material, int passed_weight, string passed_name, int passed_value): Item(passed_name, passed_value){
    durability=passed_durability;
    max_durability=passed_durability;
    material=passed_material;
    weight=passed_weight;
}
