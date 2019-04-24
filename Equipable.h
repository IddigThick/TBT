#ifndef EQUIPABLE_H
#define EQUIPABLE_H
#include "Item.h"
#include <string>//strings

using namespace std;

class Equipable : public Item{
  public:
    //constructors
    Equipable();//default > generate a completely random Equipable
    Equipable(int,int,string,int,string,int);//generate a Equipable based upon preset as defined by string
    ~Equipable() {}

    //functions to set variables
    void set_durability(unsigned short passed_durability);
    void set_max_durability(unsigned short passed_durability);
    void set_material(string passed_material);
    void set_weight(unsigned short passed_weight);

    //functions to access variables stored by class
    unsigned short get_durability();
    unsigned short get_max_durability();
    string get_material();
    unsigned short get_weight();

  protected:
    unsigned short durability;
    unsigned short max_durability;
    string material;
    unsigned short weight;
};

#endif
