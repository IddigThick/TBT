#ifndef WEAPON_H
#define WEAPON_H
#include "Equipable.h"
#include <string>

class Weapon : public Equipable
{
    public:
        Weapon();
        Weapon(int,int,string,int,string,int,string,int[],int[],char[],int,int,int,bool,int);
        string get_weapon_type();

        int get_physical_damage();
        int get_holy_damage();
        int get_ice_damage();
        int get_fire_damage();
        int get_thunder_damage();

        int get_required_strength();
        int get_required_dexterity();
        int get_required_intelligence();
        int get_required_faith();
        int get_required_corruption();

        char get_scaling_strength();
        char get_scaling_dexterity();
        char get_scaling_intelligence();
        char get_scaling_faith();
        char get_scaling_corruption();

        int get_stun_chance();
        int get_crit_chance();
        int get_parry_chance();
        int get_armor_pierce();
    protected:
        string weapon_type;

        //damage types
        int damage [5];//physical,holy,magic,fire,thunder

        //attributes
        int req_stats [5];//str,dex,int,fth,cor
        char scale_stats [5];

        unsigned short stun_chance;
        unsigned short crit_chance;
        unsigned short parry_chance;
        bool two_handed;

        unsigned short armor_pierce;
    private:
};

#endif // WEAPON_H
