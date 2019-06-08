#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H
#include <vector>
#include <string>
#include "Structures.h"

class ModuleHandler
{
    public:
        ModuleHandler();
        virtual ~ModuleHandler();
        void init();
        std::string get_item_name(std::string passed_item);
        std::string get_material_name(std::string passed_material);
        int get_equipment_type(std::string passed_item);
        Item generate_random_weapon();
        struct Weapon{
            std::string weapon_id;
            std::string name;
            double weight;
            double damage;
            double value;
            bool one_handed;
            std::vector<std::string> classes;
            //std::vector<std::string> tags; TODO - add tag system?
            Weapon(std::string passed_weapon_id,std::string passed_name,double passed_weight,double passed_damage,int passed_value,bool passed_one_handed,std::vector<std::string> passed_classes)
                : weapon_id(passed_weapon_id)
                , name(passed_name)
                , weight(passed_weight)
                , damage(passed_damage)
                , value(passed_value)
                , one_handed(passed_one_handed)
                , classes(passed_classes)
            {}
        };
        struct Material{
            std::string material_id;
            std::string name;
            double weight;//weight modifier
            double damage;//damage modifier
            double armor;//armor modifier
            double value;//value modifier
            int rarity;//rarity scale
            int difficulty;//crafting difficulty scale
            bool weapon_safe;//can this be used in weapons?
            bool armor_safe;//can this be used in armor?
            bool metal;//can this be treated as a metal?
            Material(std::string passed_material_id,std::string passed_name,double passed_weight,double passed_damage,double passed_armor,int passed_value,int passed_rarity,int passed_difficulty,bool passed_weapon_safe,bool passed_armor_safe,bool passed_metal)
                : material_id(passed_material_id)
                , name(passed_name)
                , weight(passed_weight)
                , damage(passed_damage)
                , value(passed_value)
                , rarity(passed_rarity)
                , difficulty(passed_difficulty)
                , weapon_safe(passed_weapon_safe)
                , armor_safe(passed_armor_safe)
                , metal(passed_metal)
            {}
        };
    protected:

    private:
        void load_module(std::string module_id,int module_index);
        void load_weapons(std::string module_id,int module_index);
        void load_materials(std::string module_id,int module_index);
        std::vector<std::vector<Weapon>> module_weapons;
        //std::vector<std::vector<std::vector<std::string>>> module_weapons;
        std::vector<std::vector<Material>> module_materials;
};

#endif // MODULEHANDLER_H
