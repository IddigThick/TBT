#include "Item.h"
#include "Global.h"
#include <string>//strings

using namespace std;

//functions to set variables
void Item::set_name(string passed_name) {
    name = passed_name;
}
void Item::set_value(int passed_value) {
    value = passed_value;
}

//functions to access variables stored by class
string Item::get_name() {
    return name;
}
unsigned Item::get_value() {
    return value;
}
string Item::get_item_type() {
    return item_type;
}

//implementations
Item::Item() {
    name = "DEFAULT ITEM";
    value = 100;
    item_type = "ITEM";
}
Item::Item(string passed_name, int passed_value) {
    name = passed_name;
    value = passed_value;
}
