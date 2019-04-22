#include "Drawer.h"
#include "Global.h"
#include "curses/curses.h"
#include <string>
#include <math.h>//round()

void Drawer::screen_print(string input) { //18 lines, each line has 54 max chars || print_lines lines, each line has print_length max chars
    unsigned short input_lines = ceil(((double)input.length())/print_length);//number of lines taken by input
    update_buffer(input,input_lines);
    update_print();
}
void Drawer::update_buffer(string input, unsigned short input_lines) {
    if((screen_print_line+input_lines>print_lines)) { //if the line attempting to print will exceed our screen space
        //shift all printed lines up by n lines, until the complete input may be printed, then set screen_print_line at the start of the newly cleared lines
        //TODO - before we start however, prompt user to continue.
        for(int i=0; i<print_lines-input_lines; i++) //for each buffer value which will be kept non-blank
            screen_print_buffer[i]=screen_print_buffer[i+input_lines];//push back the values
        for(int i=print_lines-input_lines; i<print_lines; i++) //DEBUG - for each line which will be replaced
            screen_print_buffer[i]="        <This will be replaced with new text>        ";//DEBUG - print replacement text, which is immediately overwritten in next loop if successful
        screen_print_line=print_lines-input_lines;
    }
    for(int i=0; i<input_lines; i++) {
        //if(i==0){//if this is the first line
        //indent the text to be printed
        //}
        if(i!=input_lines-1)//if this isn't the last line
            screen_print_buffer [screen_print_line+i] = input.substr((i*54),print_length);//print a 54 character substring
        else//if this is the last line
            screen_print_buffer [screen_print_line+i] = input.substr((i*print_length)+0,input.length());//print the rest of the string
    }
    screen_print_line+=input_lines;
}
void Drawer::update_print() {
    for(int i=0; i<print_lines; i++) {
        mvprintw(i,13,"                                                      ");//first clear printing area
        mvprintw(i,13,screen_print_buffer[i].c_str());//then print data in buffer
    }
    refresh();
}
void Drawer::draw_status_bar(int y, int x,int minimum, int maximum) {
    move(y,x);
    for(int i=10; i<=100; i+=10) {
        if(i<=(minimum*100)/maximum)//if player has all of the 10 increment chunk, display the section as a O
            addch('O');//�
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
    screen_print_line = 0;
    for(int i=0; i<print_lines; i++)
        screen_print_buffer [i] = "";
    update();
}