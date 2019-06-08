/*PROJECT INFORMATION
    cross platform status:
        Linux:
            windows.h is used in class FileInterpreter, preventing support
            otherwise, replace "#include "curses/curses.h"" with proper library (#include <ncurses.h>), and compile with flag -lncurses
*/
#include "Global.h"//global functions
#include "Character.h"

int main() {
    //initialize global colors
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_RED);

    fileInterpreter.init();//initialize fileInterpreter, loading settings/modules/load order
    moduleHandler.init();//initialize moduleHandler, loading data from modules in load order

    menu.main();//start main menu

    return 0;
}

