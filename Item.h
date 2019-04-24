#ifndef ITEM_H
#define ITEM_H
#include <string>//strings

using namespace std;

class Item {
  public:
    //constructors
    Item();//default > generate a completely random Item
    Item(string,int);//generate a Item based upon preset as defined by string
    ~Item() {}

    //functions to set variables
    void set_name(string passed_name);
    void set_value(int passed_value);

    //functions to access variables stored by class
    string get_name();
    unsigned get_value();
    string get_item_type();

  protected:
    unsigned value;
    string name;
    string item_type;
};

#endif
