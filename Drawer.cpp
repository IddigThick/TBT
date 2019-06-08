#include "Drawer.h"
#include "Global.h"

//Printing functions
void Drawer::screen_print(string input) { //18 lines, each line has 54 max chars || g_print_lines lines, each line has g_print_length max chars
    //OLD - basic check for lines to print for method where each line is ALWAYS 54 chars long
    //unsigned short input_lines = ceil(((double)input.length())/g_print_length);
    unsigned short input_lines = 0;
    string temp=input;
    while(true) {
        if(temp.length()>g_print_length) {
            input_lines+=1;
            temp = temp.substr(temp.substr(0,g_print_length-4).find_last_of(' '),temp.length());
        } else {
            input_lines+=1;
            break;
        }
    }
    update_buffer(input,input_lines);
    update_print();
}
void Drawer::line_print(string input) {
    mvprintw(17,13,">                                                     ");
    mvprintw(17,14,"%s",&input[0]);
    refresh();
    move(0,12);

}
void Drawer::update_buffer(string input, unsigned short input_lines) {
    if((screen_print_line+input_lines>g_print_lines)) { //if the line attempting to print will exceed our screen space
        //shift all printed lines up by n lines, until the complete input may be printed, then set screen_print_line at the start of the newly cleared lines
        bool flag=0;
        for(int i=0; i<g_print_lines-input_lines; i++) { //for each buffer value which will be kept non-blank
            screen_print_buffer[i]=screen_print_buffer[i+input_lines];//push back the values
            flag=true;
        }
        /*g_mode_debug - for each line which will be replaced,print replacement text, which is immediately overwritten in next loop if successful
        for(int i=g_print_lines-input_lines; i<g_print_lines; i++)
            screen_print_buffer[i]="        <This will be replaced with new text>        ";
        */
        if(flag&&!g_in_combat) { //when text will scroll out of combat, prompt user before doing so
            mvprintw(17,14,">press any key to continue...");
            getch();
            mvprintw(17,14,"                               ");
        }
        screen_print_line=g_print_lines-input_lines;
    }
    for(int i=0; i<input_lines; i++) {
        /*indent
        if(i==0&&i!=input_lines-1){//if this is the first line of a multi-line output, indent it
            int last_space = input.substr(0,g_print_length-4).find_last_of(' ');
            string temp = input.substr(0,last_space);
            input = input.substr(last_space+1,input.length());
            screen_print_buffer [screen_print_line+i] += "    "+temp;
        }*/
        if(i!=input_lines-1) { //if this isn't the first or last line
            int last_space = input.substr(0,g_print_length).find_last_of(' ');
            string temp = input.substr(0,last_space);
            input = input.substr(last_space+1,input.length());
            screen_print_buffer [screen_print_line+i] += temp;
        } else {
            screen_print_buffer [screen_print_line+i] = input.substr(0,input.length());
        }

        /*OLD - method where each line is ALWAYS 54 chars long
        if(i!=input_lines-1)//if this isn't the last line
            screen_print_buffer [screen_print_line+i] = input.substr((i*54),g_print_length);//print a 54 character substring
        else//if this is the last line
            screen_print_buffer [screen_print_line+i] = input.substr((i*g_print_length)+0,input.length());//print the rest of the string
        */
    }
    screen_print_line+=input_lines;
}
void Drawer::update_print() {
    for(int i=0; i<g_print_lines; i++) {
        mvprintw(i,13,"                                                      ");//first clear printing area
        mvprintw(i,13,screen_print_buffer[i].c_str());//then print data in buffer
    }
    move(0,12);
    refresh();
}
void Drawer::inventory_print(int character_id) {
    //TODO - re-add inventory print
    clear_screen();
    #define TARGET characters[character_id]
    for(unsigned i=0; i<TARGET.inventory.size(); i++){
        if(TARGET.inventory[i].name.compare(""))
            mvprintw(i,13,&TARGET.inventory[i].name[0]);
        else{
            mvprintw(i,13,&moduleHandler.get_material_name(TARGET.inventory[i].material_id)[0]);
            printw(" ");
            printw((moduleHandler.get_item_name(TARGET.inventory[i].item_id)).c_str());
        }
    }
    #undef TARGET
    move(0,12);
    refresh();
}
/*OLD inventory print, for item objects
void Drawer::inventory_print() {
    clear_screen();
    for(unsigned i=0; i<characters[0].inventory.size(); i++)
        //TODO - add temporary variables to make readable
        if(0==(characters[0].inventory[i]->get_name().compare(""))){//if item has no name, print material and type
            if(characters[0].inventory[i]->get_weapon_type().compare("error")==0)
                mvprintw(floor(i/2),13+(i%2)*27,"%s) %s %s",&to_string(i+1)[0],&characters[0].inventory[i]->get_material()[0],&characters[0].inventory[i]->get_armor_type()[0]);
            else
                mvprintw(floor(i/2),13+(i%2)*27,"%s) %s %s",&to_string(i+1)[0],&characters[0].inventory[i]->get_material()[0],&characters[0].inventory[i]->get_weapon_type()[0]);
        }
        else
            mvprintw(floor(i/2),13+(i%2)*27,"%s) %s",&to_string(i+1)[0],&characters[0].inventory[i]->get_name()[0]);
    for(int i=characters[0].inventory.size(); i<34; i++)
        mvprintw(floor(i/2),13+(i%2)*27,"%s)",&to_string(i+1)[0]);
    move(0,12);
    refresh();
}
*/
void Drawer::equipment_print() {
    //TODO - re-add equipment print
}
/*OLD equipment print, for item objects
void Drawer::equipment_print() {
    clear_screen();
    //each slot type for printing
    array<string,6> types = {"Weapon","Helmet","Chest","Gauntlets","Legs","Boots"};
    for(unsigned i=0; i<types.size(); i++){//for each of our types
        if(characters[0].has_equipment[i]==0)//if theres no item in the slot
            mvprintw(i,13,"%s:%s)",&to_string(i+1)[0],&types[i][0]);//print only the slot number and type
        else{
            //temporary variables, readable code
            string item_type = characters[0].equipment[i]->get_item_type();
            string weapon_type = characters[0].equipment[i]->get_weapon_type();
            string armor_type = characters[0].equipment[i]->get_armor_type();
            string material = characters[0].equipment[i]->get_material();

            if(item_type.compare("weapon")==0)//if the item is a weapon
                mvprintw(i,13,"%s:%s) %s %s",&to_string(i+1)[0],&types[i][0],&material[0],&weapon_type[0]);
            else if(item_type.compare("armor")==0)//if the item is armor
                mvprintw(i,13,"%s:%s) %s %s",&to_string(i+1)[0],&types[i][0],&material[0],&armor_type[0]);
            else
                mvprintw(i,13,"ERROR - UNKNOWN ITEM TYPE");
        }
    }
    move(0,12);
    refresh();
}
*/
void Drawer::inspect_character(int passed_id) {
    Character *target = &characters[passed_id];
    string output;
    int pronoun=0;

    //if the target is a human
    //if(target->get_race().compare("humanoid")==0)

    if(g_mode_debug)
        screen_print("g_mode_debug Armor rating = "+to_string(target->get_armor_rating()));

    //print character name and age
    output+=target->get_name()+" is a "+to_string(target->get_age())+" year old ";
    //print height
    output+=to_string(target->get_height()/12)+"'"+to_string(target->get_height()%12)+"\" ";

    /*print character masculinity, set pronoun to use
    if target has boobs -> she
    if target is feminine -> she
    if target is masculine, no boobs > he
    */
    if(target->get_masculinity()>30) {
        //output+="very masculine";
        if(target->get_breast_size()==0)
            pronoun=1;
    } else if(target->get_masculinity()>10) {
        //output+="masculine";
        if(target->get_breast_size()==0)
            pronoun=1;
    } else if(target->get_masculinity()<-30) {
        //output+="very feminine";
        pronoun=-1;
    } else if(target->get_masculinity()<-10) {
        //output+="feminine";
        pronoun=-1;
    } else {
        //output+="androgynous";
        pronoun=0;
    }
    //characters always assume others with boobs are female
    if(target->get_breast_size()>100)
        pronoun=-1;

    //print type of character
    output+="human. ";
    /*output correct sex
    if(target->has_penis&&target->has_vagina)
        output+="hermaphrodite. ";
    else if(target->has_penis&&pronoun==-1)
        output+="trap. ";
    else if(target->has_penis)
        output+="male. ";
    else
        output+="female. ";
    */
    //explain interpreted sex
    if(pronoun==-1&&target->has_penis) {
        if(target->get_breast_size()>100)
            output+="Because of "+target->get_name()+"'s noticeable bust, everyone assumes they're female. ";
        else
            output+="Because of "+target->get_name()+"'s cute, feminine face, everyone assumes they're female. ";
    }
    else if(pronoun==-1){
        if(target->get_masculinity()<-30)
            output+="She has a pretty, very feminine face, leading everyone to correctly assume she's a female";
        else
            output+="She has a cute, feminine face, leading everyone to correctly assume she's a female";
        if(target->get_breast_size()<=199)
            output+=", despite her small chest";
        output+=". ";
    }
    else if(pronoun==1){
        if(target->get_masculinity()>30)
            output+="He has a rugged, very masculine face, leading everyone to correctly assume he's a male. ";
        else
            output+="He has a normal, masculine face, leading everyone to correctly assume he's a male. ";
    }
    else{
        output+="Because of their androgynous features, people aren't sure of "+target->get_name()+"'s sex. ";
    }
    //pronoun based possessive
    if(pronoun==1)
        output+="He has ";
    else if(pronoun==-1)
        output+="She has ";
    else
        output+="They have ";

    //print skin,hair, and eye color
    output+=g_names_colors_skin[target->get_skin_color()]+" skin, "+g_names_colors_hair[target->get_hair_color()]+" hair, and "+g_names_colors_eye[target->get_eye_color()]+" eyes.";
    //output first paragraph
    screen_print(output);
    screen_print(" ");

    output="";

    //everything past this line is NSFW
    if(g_mode_sfw==1)
        return;

    //pronoun based possessive, consider moving to function
    if(pronoun==1)
        output+="He has a ";
    else if(pronoun==-1)
        output+="She has a ";
    else
        output+="They have a ";

    //print penis data
    if(target->has_penis)
        output+=to_string(target->get_penis_size())+" inch penis, and a ";

    //print chest data
    if(target->get_breast_size()/100!=0)
        output+="pair of ";

    //actual breast size flat:0-99,AAA:100-199,AA:200-299,A:300-399
    switch(target->get_breast_size()/100) { //FLAT,AAA,AA,A,B,C,D,E,F,G,H
    case 0://flat
        output+="completely flat chest";
        break;
    case 1://AAA
        output+="unnoticeable, AAA";
        break;
    case 2://AA
        output+="barely noticeable, AA";
        break;
    case 3://A
        output+="tiny, A";
        break;
    case 4://B
        output+="small, B";
        break;
    case 5://C
        output+="average-sized, C";
        break;
    case 6://D
        output+="large, D";
        break;
    case 8://E
        output+="large, E";
        break;
    case 10://F
    case 11:
        output+="large, F";
        break;
    case 12://G
    case 13:
        output+="sizable, G";
        break;
    case 14://H
    case 15:
        output+="huge, H";
        break;
    case 16:
    case 17:
        output+="massive, I";
        break;
    case 18:
    case 19:
        output+="massive, J";
        break;
    case 20:
    case 21:
    case 22:
        output+="massive, K";
        break;
    default:
        output+="absurdly large, ?";
        break;
    }

    if(target->get_breast_size()>99)
        output+="-cup ";
    if(target->get_breast_size()>99&&target->get_breast_size()<1200) {
        switch(rand() % 4) {
        case 0:
            output+="boobs";
            break;
        case 1:
            output+="tits";
            break;
        case 2:
            output+="boobs";
            break;
        case 3:
            output+="breasts";
            break;
            //mammies,udders,pillows,melons
        }
    } else if(target->get_breast_size()>99)
        output+="udders";
    output+=", each with a ";
    if(target->get_nipples_size()>=10)
        output+="big";
    else if(target->get_nipples_size()>=5)
        output+="large";
    else if(target->get_nipples_size()>=3)
        output+="small";
    else
        output+="tiny";
    output+=", "+to_string(target->get_nipples_size()/10)+"."+to_string(target->get_nipples_size()%10)+" inch nipple, and a ";
    switch(target->get_areolae_size()/10){
    case 0:
        output+="tiny";
        break;
    case 1:
        output+="small";
        break;
    case 2:
        output+="medium-sized";
        break;
    case 3:
        output+="large";
        break;
    case 4:
        output+="huge";
        break;
    case 5:
        output+="giant";
        break;
    }
    output+=" areola";
    screen_print(output);
    move(0,12);
    refresh();
}
/*
void Drawer::inspect_item(Item &passed_item) {
    if(0==(passed_item.get_item_type().compare("weapon"))) { //if item is a weapon
        //weapon's full name
        mvprintw(0,13,"%s %s \"%s\"",&passed_item.get_material()[0],&passed_item.get_weapon_type()[0],&passed_item.get_name()[0]);
        //damage box
        mvprintw(9,13,"DAMAGE");
        mvprintw(10,13,"PHY: %s",&to_string(passed_item.get_physical_damage())[0]);
        mvprintw(11,13,"HLY: %s",&to_string(passed_item.get_holy_damage())[0]);
        mvprintw(12,13,"ICE: %s",&to_string(passed_item.get_ice_damage())[0]);
        mvprintw(13,13,"FRE: %s",&to_string(passed_item.get_fire_damage())[0]);
        mvprintw(14,13,"THN: %s",&to_string(passed_item.get_thunder_damage())[0]);
        //stats box
        mvprintw(2,13," SCALE|REQUIRED");
        mvprintw(3,13,"STR: %c|%s",passed_item.get_scaling_strength(),&to_string(passed_item.get_required_strength())[0]);
        mvprintw(4,13,"DEX: %c|%s",passed_item.get_scaling_dexterity(),&to_string(passed_item.get_required_dexterity())[0]);
        mvprintw(5,13,"INT: %c|%s",passed_item.get_scaling_intelligence(),&to_string(passed_item.get_required_intelligence())[0]);
        mvprintw(6,13,"FTH: %c|%s",passed_item.get_scaling_faith(),&to_string(passed_item.get_required_faith())[0]);
        mvprintw(7,13,"COR: %c|%s",passed_item.get_scaling_corruption(),&to_string(passed_item.get_required_corruption())[0]);
        //chances box
        mvprintw(2,33,"CHANCES");
        mvprintw(3,33,"STN: %s%%",&to_string(passed_item.get_stun_chance())[0]);
        mvprintw(4,33,"CRT: %s%%",&to_string(passed_item.get_crit_chance())[0]);
        mvprintw(5,33,"PRY: %s%%",&to_string(passed_item.get_parry_chance())[0]);
        mvprintw(6,33,"AP : %s%%",&to_string(passed_item.get_armor_pierce())[0]);
        move(0,12);
        refresh();
    } else if(0==(passed_item.get_item_type().compare("armor"))) { //if item is a weapon
        if(0==(passed_item.get_name().compare("")))
            mvprintw(0,13,"%s %s",&passed_item.get_material()[0],&passed_item.get_armor_type()[0]);
        else
            mvprintw(0,13,"%s %s \"%s\"",&passed_item.get_material()[0],&passed_item.get_armor_type()[0],&passed_item.get_name()[0]);
        mvprintw(1,13,"Item type:%s",&passed_item.get_item_type()[0]);
        move(0,12);
        refresh();
    }
}
*/
void Drawer::options_print(string options[]){
    mvprintw(19,13," Q-           W-           E-           R-          ");
    mvprintw(21,13," A-           S-           D-           F-          ");
    mvprintw(23,13," Z-           X-           C-           V-          ");
    int counter=0;
    for(int column = 19;column<=23;column+=2)
        for(int row = 13; row<=55 ;row+=13){
            mvprintw(column,row+3,options[counter].c_str());
            counter++;
        }
}
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
    move(0,12);
}
void Drawer::minimap() {
}
void Drawer::player_status() {
    //clear printing space
    for(int i=0; i<14; i++)
        mvprintw(i,0,"           ");
    //Character player = *characters.begin();//the drawer draws the player status, can NOT operate before character is created
    mvprintw(0,0,&characters[0].get_name()[0]);//print name
    //print health data
    mvprintw(2,0,"HP:%s/%s",&to_string(characters[0].get_health())[0],&to_string(characters[0].get_max_health())[0]);
    draw_status_bar(3,0,characters[0].get_health(),characters[0].get_max_health());
    //print stamina data
    mvprintw(4,0,"AP:%s/%s",&to_string(characters[0].get_stamina())[0],&to_string(characters[0].get_max_stamina())[0]);
    draw_status_bar(5,0,characters[0].get_stamina(),characters[0].get_max_stamina());
    //print mana data
    mvprintw(6,0,"MP:%s/%s",&to_string(characters[0].get_mana())[0],&to_string(characters[0].get_max_mana())[0]);
    draw_status_bar(7,0,characters[0].get_mana(),characters[0].get_max_mana());
    //print lust data
    mvprintw(8,0,"LP:%s/%s",&to_string(characters[0].get_lust())[0],&to_string(characters[0].get_max_lust())[0]);
    draw_status_bar(9,0,characters[0].get_lust(),characters[0].get_max_lust());
    //print level
    mvprintw(11,0,"LVL:%s",&to_string(characters[0].get_level())[0]);
    //print experience data
    mvprintw(12,0,"XP:%s/%s",&to_string(characters[0].get_experience())[0],&to_string(characters[0].get_max_experience())[0]);
    draw_status_bar(13,0,characters[0].get_experience(),characters[0].get_max_experience());
    move(0,12);
}
void Drawer::target_status(int passed_id) {
    //clear right panel
    for(int i=0; i<24; i++)
        mvprintw(i,69,"           ");
    Character *target = &characters[passed_id];
    //Character target = *characters.begin();//the drawer draws the target status, can NOT operate before character is created
    mvprintw(0,69,&target->get_name()[0]);//print name
    //print health data
    mvprintw(2,69,"HP:%s/%s",&to_string(target->get_health())[0],&to_string(target->get_max_health())[0]);
    draw_status_bar(3,69,target->get_health(),target->get_max_health());
    //print stamina data
    mvprintw(4,69,"AP:%s/%s",&to_string(target->get_stamina())[0],&to_string(target->get_max_stamina())[0]);
    draw_status_bar(5,69,target->get_stamina(),target->get_max_stamina());
    //print mana data
    mvprintw(6,69,"MP:%s/%s",&to_string(target->get_mana())[0],&to_string(target->get_max_mana())[0]);
    draw_status_bar(7,69,target->get_mana(),target->get_max_mana());
    //print lust data
    mvprintw(8,69,"LP:%s/%s",&to_string(target->get_lust())[0],&to_string(target->get_max_lust())[0]);
    draw_status_bar(9,69,target->get_lust(),target->get_max_lust());
    //print level
    mvprintw(11,69,"LVL:%s",&to_string(target->get_level())[0]);
    mvprintw(12,69,"ID:%s",&to_string(passed_id)[0]);//g_mode_debug - print character id
    move(0,12);
}
void Drawer::borders() {
    move(18,0);
    hline('-',68);
    move(0,11);
    vline('|',100);
    move(0,68);
    vline('|',100);
    move(0,12);
}
void Drawer::clear_screen() {
    for(int i=0; i<g_print_lines; i++) {
        mvprintw(i,12,"                                                       ");//clear printing area
    }
    refresh();
    move(0,12);
}
void Drawer::clear_buffer() {
    for(int i=0; i<18; i++)
        screen_print_buffer[i]="";//remove all stored strings
    screen_print_line=0;//reset printer back to top
}
void Drawer::clear_line() {
    mvprintw(17,13,">                                                     ");
    refresh();
    move(0,12);
}
void Drawer::clear_options() {
    mvprintw(19,13,"                                                    ");
    mvprintw(21,13,"                                                    ");
    mvprintw(23,13,"                                                    ");
}
void Drawer::update() {
    borders();
    player_status();
    minimap();
    refresh();
}
void Drawer::exit() {
    endwin();
}
void Drawer::init() {
    initscr();
    noecho();
    curs_set(0);
    screen_print_line = 0;
    for(int i=0; i<g_print_lines; i++)
        screen_print_buffer [i] = "";
    update();
}
void Drawer::npcs() {};//handled by mapper, change?/REMOVE
void Drawer::items() {};//handled by mapper,change?/REMOVE
int holder;
//implementations
Drawer::Drawer() {
}
