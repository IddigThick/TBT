//standard libraries
#include <iostream>//cin, cout FOR DEBUG, PLEASE REMOVE
#include <string>//strings
#include <vector>//vectors
#include <stdlib.h>//rand()
#include <math.h>//round()
#include <time.h>//proper rand based upon clock
//external libraries
#include "curses/curses.h"//formatted printing to console
//user libraries
#include "Global.h"
#include "Character.h"
#include "Drawer.h"

using namespace std;

int main() {
    //generate seed for rand
    time_t t;
    srand((unsigned) time(&t));

    //DEBUG - generate random characters
    Character *f1;
    for (int n=0; n<3; n++) {
        f1 = new Character("random");
        characters.push_back(*f1);
    }
    //DEBUG - test player link to characters[0]
    Character *player = &characters[0];
    player->set_name("Player");
    //player.set_name("Player");
    player->printCharacterInfo();

    //DEBUG - display info of random Characters generated
    vector<Character>::iterator it;
    for ( it = characters.begin(); it != characters.end(); ++it ) {
        it->printCharacterInfo();
    }
    cin.get();

    //DEBUG - test draw.screen_print function
    Drawer draw;
    draw.screen_print("Bellow are 2 draw.screen_print(), lorem and At vero:");
    draw.screen_print("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    draw.screen_print("At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis praesentium voluptatum deleniti atque corrupti quos dolores et quas molestias excepturi sint occaecati cupiditate non provident, similique sunt in culpa qui officia deserunt mollitia animi, id est laborum et dolorum fuga. Et harum quidem rerum facilis est et expedita distinctio.");
    draw.screen_print("This is the last line");//last test line before scroll
    cin.get();
    draw.screen_print("This is a new line of text, which scrolls the above text by 2 lines");
    cin.get();
    draw.screen_print(" ");//equivalent to newline
    draw.screen_print("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    cin.get();

    return 0;
}

