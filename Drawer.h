#ifndef DRAWER_H
#define DRAWER_H
#include <string>
#include "Global.h"
#include "Weapon.h"
#include "Item.h"


using namespace std;

class Drawer {
  public:
    Drawer();
    ~Drawer() {}
    void screen_print(string input);
    void inspect_weapon_print(Weapon*);
    void update_print();
  private:
    void update_buffer(string input, unsigned short input_lines);
    void draw_status_bar(int y, int x,int minimum, int maximum);
    void player_status();
    void borders();
    void update();
    void exit();
    void npcs();
    void items();
    unsigned short screen_print_line;
    string screen_print_buffer [18];
};

#endif // DRAWER_H
