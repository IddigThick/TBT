#ifndef MENU_H
#define MENU_H
#include <string>


class Menu
{
    public:
        Menu();
        virtual ~Menu();
        void main();
        void creation_start();
        void creation_ability();
        void creation_race();
        void creation_class();
        void creation_appearance();
        int print_options(int args,int print_loc_x,int print_loc_y,int start_index,std::string options[]);
        void settings();
        void modules();
    protected:

    private:
};

#endif // MENU_H
