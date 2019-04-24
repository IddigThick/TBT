#include <vector>
#include "Character.h"
#include "Item.h"
using namespace std;
extern int myVar;
extern vector<Character> characters;
extern vector<Item*> items;
//player settings - TODO load these parameters from config file at launch if exists, otherwise create config with default values
extern unsigned short max_age;
extern unsigned short min_age;
extern unsigned short max_height;//remove?
extern unsigned short min_height;//remove?
extern const unsigned short print_lines;
extern const int print_length;
extern Character player;
