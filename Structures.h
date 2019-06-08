#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <string>
#include <vector>

//global structures
struct Item{
	std::string item_id;//base.weapon.axe
	std::string material_id;//base.material.iron
	std::string name;//Excalibur
	int durability;//100, total is defined by item_id and material
	std::vector<std::string> enchantments;//base.enchantment.fortitude,etc...

	Item() : item_id("base.weapon.short_sword"){}
    Item(std::string passed_item_id,std::string passed_material_id,int passed_durability)
        : item_id(passed_item_id)
        , material_id(passed_material_id)
        , durability(passed_durability)
    {}
    Item(std::string passed_item_id,std::string passed_material_id,std::string passed_name, int passed_durability)
        : item_id(passed_item_id)
        , material_id(passed_material_id)
        , name(passed_name)
        , durability(passed_durability)
    {}
};
#endif // STRUCTURES_H
