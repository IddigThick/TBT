#include "Drawer.h"
#include "Global.h"
#include "curses/curses.h"

    void Drawer::draw_status_bar(int y, int x,int minimum, int maximum) {
        move(y,x);
        for(int i=10; i<=100; i+=10) {
            if(i<=(minimum*100)/maximum)//if player has all of the 10 increment chunk, display the section as a O
                addch('O');//×
            else if(10>i-minimum&&i-minimum>0)//if player has a portion of the chunk, display o
                addch('o');
            else
                addch('_');//if player has none of the chunk, display _
        }
    }
    void Drawer::player_status() {
        Character player = *characters.begin();//the drawer draws the player status, can NOT operate before character is created
        mvprintw(0,0,&player.get_name()[0]);//print name
        //print health data
        mvprintw(2,0,"HP:%s/%s",&to_string(player.get_health())[0],&to_string(player.get_max_health())[0]);
        draw_status_bar(3,0,player.get_health(),player.get_max_health());
        //print stamina data
        mvprintw(4,0,"AP:%s/%s",&to_string(player.get_stamina())[0],&to_string(player.get_max_stamina())[0]);
        draw_status_bar(5,0,player.get_stamina(),player.get_max_stamina());
        //print mana data
        mvprintw(6,0,"MP:%s/%s",&to_string(player.get_mana())[0],&to_string(player.get_max_mana())[0]);
        draw_status_bar(7,0,player.get_mana(),player.get_max_mana());
        //print lust data
        mvprintw(8,0,"LP:%s/%s",&to_string(player.get_lust())[0],&to_string(player.get_max_lust())[0]);
        draw_status_bar(9,0,player.get_lust(),player.get_max_lust());
        //print level
        mvprintw(11,0,"LVL:%s",&to_string(player.get_level())[0]);
        //print experience data
        mvprintw(12,0,"XP:%s/%s",&to_string(player.get_experience())[0],&to_string(player.get_max_experience())[0]);
        draw_status_bar(13,0,player.get_experience(),player.get_max_experience());
    }
    void Drawer::borders() {
        move(18,0);
        hline('-',68);
        move(0,11);
        vline('|',100);
        move(0,68);
        vline('|',100);
        move(0,0);
    }
    void Drawer::update() {
        borders();
        player_status();
        refresh();
    }
    void Drawer::exit() {
        endwin();
    }
    void Drawer::npcs() {};
    void Drawer::items() {};
    int holder;
//implementations
Drawer::Drawer() {
    initscr();
    (void)echo();
    curs_set(0);
    update();
}
