#include "Global.h"
#include <vector>
#include "Character.h"
using namespace std;
int myVar = 0;  // initialize
//player settings - TODO load these parameters from config file at launch if exists, otherwise create config with default values
unsigned short max_age=50;
unsigned short min_age=12;
unsigned short max_height=96;//remove?
unsigned short min_height=48;//remove?
const unsigned short print_lines=18;
const int print_length=54;
vector<Character> characters;
