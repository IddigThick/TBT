#include "Weapon.h"
#include "Global.h"
#include "Equipable.h"
#include "Drawer.h"
#include <string.h>

using namespace std;

//functions to set variables


//functions to access variables stored by class
string Weapon::get_weapon_type(){
    return weapon_type;
}
int Weapon::get_physical_damage(){
    return damage[0];
}
int Weapon::get_holy_damage(){
    return damage[1];
}
int Weapon::get_ice_damage(){
    return damage[2];
}
int Weapon::get_fire_damage(){
    return damage[3];
}
int Weapon::get_thunder_damage(){
    return damage[4];
}
//required stats
int Weapon::get_required_strength(){
    return req_stats[0];
}
int Weapon::get_required_dexterity(){
    return req_stats[1];
}
int Weapon::get_required_intelligence(){
    return req_stats[2];
}
int Weapon::get_required_faith(){
    return req_stats[3];
}
int Weapon::get_required_corruption(){
    return req_stats[4];
}
//scaling stats
char Weapon::get_scaling_strength(){
    return scale_stats[0];
}
char Weapon::get_scaling_dexterity(){
    return scale_stats[1];
}
char Weapon::get_scaling_intelligence(){
    return scale_stats[2];
}
char Weapon::get_scaling_faith(){
    return scale_stats[3];
}
char Weapon::get_scaling_corruption(){
    return scale_stats[4];
}
//special stats
int Weapon::get_stun_chance(){
    return stun_chance;
}
int Weapon::get_crit_chance(){
    return crit_chance;
}
int Weapon::get_parry_chance(){
    return parry_chance;
}
int Weapon::get_armor_pierce(){
    return armor_pierce;
}

//implementations
Weapon::Weapon() {
    weapon_type="error";
}
Weapon::Weapon(int passed_durability,int passed_max_durability,string passed_material,int passed_weight,string passed_name,int passed_value,string passed_type,int passed_damage[],int passed_req_stats[],char passed_scale_stats[],int passed_stun_chance,int passed_crit_chance,int passed_parry_chance,bool two_handed,int passed_armor_pierce): Equipable(passed_durability,passed_max_durability,passed_material,passed_weight,passed_name,passed_value){
    item_type="weapon";
    weapon_type="dagger";
    memcpy(damage,passed_damage,sizeof(damage));
    memcpy(req_stats,passed_req_stats,sizeof(req_stats));
    memcpy(scale_stats,passed_scale_stats,sizeof(scale_stats));
    stun_chance=passed_stun_chance;
    crit_chance=passed_crit_chance;
    parry_chance=passed_parry_chance;
    armor_pierce=passed_armor_pierce;
}
