#ifndef ITEM_H
#define ITEM_H
#include <string>//strings

using namespace std;//TODO - this probly shouldn't be here

class Item {
  public:
    //constructors
    Item();//default > generate a completely random Item
    Item(string,int);//generate a Item based upon preset as defined by string

    //functions to set variables
    void set_name(string passed_name);
    void set_value(int passed_value);

    //functions to access variables stored by class
    string get_name();
    unsigned get_value();
    string get_item_type();

    //for derived class Equipable
    virtual void set_durability(unsigned short passed_durability) = 0;
    virtual void set_max_durability(unsigned short passed_durability) = 0;
    virtual void set_material(string passed_material) = 0;
    virtual void set_weight(unsigned short passed_weight) = 0;

    virtual unsigned short get_durability() = 0;
    virtual unsigned short get_max_durability() = 0;
    virtual string get_material() = 0;
    virtual unsigned short get_weight() = 0;


    //for derived class Weapon
    virtual string get_weapon_type(){
        return "error";
    };
    virtual int get_physical_damage() {return 0;};
    virtual int get_holy_damage() {return 0;};
    virtual int get_ice_damage() {return 0;};
    virtual int get_fire_damage() {return 0;};
    virtual int get_thunder_damage() {return 0;};
    virtual int get_total_damage() {return 0;};

    virtual int get_required_strength() {return 0;};
    virtual int get_required_dexterity() {return 0;};
    virtual int get_required_intelligence() {return 0;};
    virtual int get_required_faith() {return 0;};
    virtual int get_required_corruption() {return 0;};

    virtual char get_scaling_strength() {return 0;};
    virtual char get_scaling_dexterity() {return 0;};
    virtual char get_scaling_intelligence() {return 0;};
    virtual char get_scaling_faith() {return 0;};
    virtual char get_scaling_corruption() {return 0;};

    virtual int get_stun_chance() {return 0;};
    virtual int get_crit_chance() {return 0;};
    virtual int get_parry_chance() {return 0;};
    virtual int get_armor_pierce() {return 0;};

    //for derived class Armor
    virtual string get_armor_type(){
        return "error";
    };
    virtual int get_armor_rating() {return 0;};

    //virtual ~Item() = 0;
  protected:
    string item_type;
    unsigned value;
    string name;

};
#endif
