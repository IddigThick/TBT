#ifndef DRAWER_H
#define DRAWER_H

#include <string>
#include <math.h>//round()

#include "curses/curses.h"

class Drawer {
  public:
    Drawer();
    ~Drawer() {}
    void screen_print(std::string input);
    void line_print(std::string input);
    void inspect_character(int passed_id);
    //void inspect_weapon_print(Weapon*);
    //void inspect_item(Item &passed_item);
    void update_print();
    void inventory_print(int character_id);
    void equipment_print();
    void options_print(std::string options[12]);
    void clear_screen();
    void clear_buffer();
    void clear_line();
    void clear_options();
    void target_status(int passed_id);
    void update();
    void init();

  private:
    void update_buffer(std::string input, unsigned short input_lines);
    void draw_status_bar(int y, int x,int minimum, int maximum);
    void minimap();
    void player_status();
    void borders();
    void exit();
    void npcs();
    void items();
    unsigned short screen_print_line;
    std::string screen_print_buffer [18];
};

#endif // DRAWER_H
