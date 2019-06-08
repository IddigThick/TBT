#include "Menu.h"
#include "Global.h"//global vars
#include "curses/curses.h"//for printing

void Menu::main() {
    initscr();//start curses
    curs_set(0);//disable cursor
    noecho();//disable input display
    start_color();//enable colors
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_RED);

    //raw();
    //nonl();

    string options[] = {"Continue","New","Load","Settings","Modules","Quit"};
    while(true) {

        mvprintw(10,34,"Welcome to TBT");
        mvprintw(24,0,"INDEV");
        switch(print_options(6,11,39,0,options)) {
        case 0:
            if(g_game_active)
                controller.movement();
        case 2:
            attron(COLOR_PAIR(1));
            mvprintw(0,0,"Sorry, saves not implemented yet!");
            attroff(COLOR_PAIR(1));
            getch();
            clear();
            break;
        case 1:
            clear();
            creation_start();
            break;
        case 3:
            clear();
            settings();
        case 4:
            clear();
            modules();
        case 5:
            exit(EXIT_SUCCESS);
        }
    }
}
void Menu::settings() {
    attron(COLOR_PAIR(1));
    mvprintw(0,0,"Settings");
    attroff(COLOR_PAIR(1));
    getch();
    clear();
    main();
}
void Menu::modules() {
    int print_line=1;
    attron(COLOR_PAIR(1));
    mvprintw(0,0,"Modules");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(1));
    for(unsigned short i=0;i<g_load_order.size();i++){
        mvprintw(print_line,13,&g_load_order[i][0]);
        print_line++;
    }
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    for(unsigned short i=0;i<g_modules.size();i++){
        mvprintw(print_line,13,&g_modules[i][0]);
        print_line++;
    }
    attroff(COLOR_PAIR(2));
    getch();
    clear();
    main();
}
void Menu::creation_start() {
    mvprintw(0,0,"[opening dialog goes here]");
    //mvprintw(0,0,"  You are an adventurer on the world of Terra, the cradle of life within the\nendless void of space. Terra is a world in which many species live in both\nharmony and conflict. The world is dominated by Humans, and they are considered by many to be the favored race of the Gods. Terra exists within the material\nworld, but the immaterial world is just as real. The immaterial is where what humans call Heaven and Hell both exist, each with their respective benevolent and benevolent forces.");
    //mvprintw(7,0,"\n  You, like many other adventurers, have traveled to the land of Avalon. The\ncontinent is centered around Mount Nexus, which functions as the Axis mundi of\nTerra, the place in which the immaterial and material world are connected. Due\nto Avalons proximity to this connection, the boundary between the two worlds is extremely thin, allowing it to be a realm of fantasy otherwise unseen.");
    //mvprintw(24,0,"press any key to continue...");
    mvprintw(2,0,"press any key to continue...");
    getch();
    clear();
    creation_ability();
}

void Menu::creation_ability() {
    int values[] = {10,10,10,10,10,10};
    int points = g_starting_ability_points;
    if(characters[0].get_race().compare("human")!=0)
        points+=2;
    string options[] = {"STR","DEX","CON","INT","WIS","CHA"};
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    int ch;
    unsigned short selection = 0;
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(0,0,"Create Your Character");
    attroff(COLOR_PAIR(1));
    while(true) {
        move(1,0);
        clrtobot();
        mvprintw(2,0," Assign Ability Points");
        mvprintw(9,3,"Remaining: ");
        printw("%i",points);

        for(int i=0; i<7; i++){
            if(i!=6)
                mvprintw(3+i,3,"%s ",&options[i][0]);
            else
                move(5+i,3);
            if(i==selection)
                attron(COLOR_PAIR(1));
            if(i!=6){
                printw("< %i",values[i]);
                if(values[i]>9)
                    printw(" >");
                else
                    printw("  >");
            }
            else
                printw("< CONTINUE >");
            if(i==selection)
                attroff(COLOR_PAIR(1));
        }

        switch(selection) {
        case 0:
            mvprintw(20,1,"Strength measures your character's muscle and physical power. This ability is\n especially important for fighters, barbarians, paladins, rangers, and monks\n because it helps them prevail in combat.");
            break;
        case 1:
            mvprintw(20,1,"Dexterity measures agility, reflexes, and balance. This ability is the most \n important one for rogues, but it's also useful for characters who wear light\n or medium armor or no armor at all. ");
            break;
        case 2:
            mvprintw(20,1,"Constitution represents your character's health and stamina. A Constitution \n bonus increases a character's hit points, so the ability is important for all\n classes.");
            break;
        case 3:
            mvprintw(20,1,"Intelligence determines how well your character learns and reasons. This\n ability is important for wizards, and any character who wants to have a wide\n assortment of skills");
            break;
        case 4:
            mvprintw(20,1,"Wisdom describes a character's willpower, common sense, perception, and\n intuition. While intelligence represents one's ability to analyze information,\n wisdom represents being in tune with and aware of one's surroundings. Wisdom is the most important ability for clerics and druids, and is also important for\n paladins and rangers.");
            break;
        case 5:
            mvprintw(20,1,"Charisma measures a character's force of personality, persuasiveness,\n personal magnetism, ability to lead, and physical attractiveness. Charisma is\n most important for paladins, sorcerers, and bards.");
            break;
        }
        refresh();
        ch = getch();
        switch (ch) {
        case 10:
            if(selection==6){
                characters[0].set_str(values[0]);
                characters[0].set_dex(values[1]);
                characters[0].set_con(values[2]);
                characters[0].set_int(values[3]);
                characters[0].set_wis(values[4]);
                characters[0].set_cha(values[5]);

                creation_race();
            }
            break;
        case KEY_UP:
            if(selection>0)
                selection-=1;
            break;
        case KEY_DOWN:
            if(selection<6)
                selection+=1;
            break;
        case KEY_LEFT:
            if(values[selection]>7){
                switch(values[selection]){
                case 8:
                    points+=2;
                    break;
                case 9:
                    points+=1;
                    break;
                case 10:
                    points+=1;
                    break;
                case 11:
                    points+=1;
                    break;
                case 12:
                    points+=1;
                    break;
                case 13:
                    points+=1;
                    break;
                case 14:
                    points+=2;
                    break;
                case 15:
                    points+=2;
                    break;
                case 16:
                    points+=3;
                    break;
                case 17:
                    points+=3;
                    break;
                case 18:
                    points+=4;
                    break;
                }
                values[selection]-=1;
            }

            break;
        case KEY_RIGHT:
            if(points>0){
                int temp = points;
                switch(values[selection]){
                case 7:
                    if(points>=2)
                        points-=2;
                    break;
                case 8:
                    if(points>=1)
                        points-=1;
                    break;
                case 9:
                    if(points>=1)
                        points-=1;
                    break;
                case 10:
                    if(points>=1)
                        points-=1;
                    break;
                case 11:
                    if(points>=1)
                        points-=1;
                    break;
                case 12:
                    if(points>=1)
                        points-=1;
                    break;
                case 13:
                    if(points>=2)
                        points-=2;
                    break;
                case 14:
                    if(points>=2)
                        points-=2;
                    break;
                case 15:
                    if(points>=3)
                        points-=3;
                    break;
                case 16:
                    if(points>=3)
                        points-=3;
                    break;
                case 17:
                    if(points>=4)
                        points-=4;
                    break;
                }
                if(temp!=points)
                    values[selection]+=1;
            }
            break;
        }
    }
}

void Menu::creation_race() {
    //want to print strings, cant use generic options
    string options[] = {"Wolf-folk","Cat-folk","Kobold","Human","Elf","Orc"};
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    int ch;
    unsigned short selection = 0;
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(0,0,"Create Your Character");
    attroff(COLOR_PAIR(1));
    while(true) {
        move(1,0);
        clrtobot();
        mvprintw(2,0," Select Your Race");
        mvprintw(2,20,"Racial Benefits");
        for(int i=0; i<6; i++)
            mvprintw(3+i,7,"|%s",&options[i][0]);
        if(selection!=3){
            attron(COLOR_PAIR(2));
            mvprintw(3+selection,7,"|%s",&options[selection][0]);
            attroff(COLOR_PAIR(2));
        }else{
            attron(COLOR_PAIR(1));
            mvprintw(3+selection,7,"|%s",&options[selection][0]);
            attroff(COLOR_PAIR(1));
        }

        switch(selection) {
        case 2:
            mvprintw(20,1,"Kobolds rarely leave their cozy warrens by their own choice. Most of those who\n set out on adventures are the last of their tribe, and such individuals often\n settle down again as soon as they find another kobold community willing to take them in. Kobolds who cannot rein in, or at least conceal, their spiteful and\n malicious natures have great difficulty surviving in the larger world.");
            break;
        case 3:
            mvprintw(3,21,"+2 to any ability score");
            mvprintw(4,21,"+1 skill rank when you gain a level");
            mvprintw(5,21,"+1 skill rank at first level");
            mvprintw(6,21,"+1 feat at 1st level");
            mvprintw(20,1,"Ambitious, sometimes heroic, and always confident, humans have an ability to\n work together toward common goals that makes them a force to be reckoned with.\n Though short-lived compared to other races, their boundless energy and drive\n allow them to accomplish much in their brief lifetimes.");
            break;
        case 4:
            mvprintw(3,21,"+2 DEX, +2 INT, and -2 CON");
            mvprintw(4,21,"+2 perception bonus");
            mvprintw(5,21,"+2 bonus against spell resistance ");
            mvprintw(6,21,"+2 identify magic item bonus");
            mvprintw(20,1,"Tall, noble, and often haughty, elves are long-lived and subtle masters of the wilderness. Elves excel in the arcane arts. Often they use their intrinsic link to nature to forge new spells and create wondrous items that, like their creators, seem nearly impervious to the ravages of time. A private and often introverted race, elves can give the impression they are indifferent to the plights of others.");
            break;
        case 0:
            mvprintw(20,1,"Wolf-folk description");
        }
        refresh();
        ch = getch();
        switch (ch) {
        case KEY_UP:
            if(selection>0)
                selection-=1;
            break;
        case KEY_DOWN:
            if(selection<6-1)
                selection+=1;
            break;
        case 10:
            switch(selection) {
            case 3:
                characters[0].set_race("human");
                creation_class();
                break;
            }
            break;
        }
    }
}

void Menu::creation_class() {
    //want to print strings, cant use generic options
    string options[] = {"Cleric","Fighter","Monk","Paladin","Ranger","Rogue","Wizard"};
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    int ch;
    unsigned short selection = 0;
    while(true) {
        move(1,0);
        clrtobot();
        mvprintw(2,0," Select Your Class");
        mvprintw(2,20,"Class Features");
        for(int i=0; i<7; i++)
            mvprintw(3+i,7,"|%s",&options[i][0]);
        if(selection>0&&selection<4){
            attron(COLOR_PAIR(1));
            mvprintw(3+selection,7,"|%s",&options[selection][0]);
            attroff(COLOR_PAIR(1));
        }else{
            attron(COLOR_PAIR(2));
            mvprintw(3+selection,7,"|%s",&options[selection][0]);
            attroff(COLOR_PAIR(2));
        }

        switch(selection) {
        case 1:
            mvprintw(3,21,"Major Skills: One-handed, Two-handed, Medium/Heavy Armor,");
            mvprintw(4,21,"Skills/Level: 2 + Int mod");
            mvprintw(5,21,"Alignment: Any");
            mvprintw(6,21,"Hit Die: d10");

            mvprintw(20,1,"Fighters excel at combat-defeating their enemies, controlling the flow of\n battle, and surviving such sorties themselves. While their specific weapons and methods grant them a wide variety of tactics, few can match fighters for sheer  battle prowess.");
            break;
        case 2:
            mvprintw(3,21,"Major Skills: Unarmed, Light Armor, Unarmored");
            mvprintw(4,21,"Skills/Level: 4 + Int mod");
            mvprintw(5,21,"Alignment: Any Lawful");
            mvprintw(6,21,"Hit Die: d8");

            mvprintw(20,1,"Monks excel at overcoming even the most daunting perils, striking where it's\n least expected, and taking advantage of enemy vulnerabilities. They find\n their bodies to be just as capable of crippling or killing as any blade.");
            break;
        case 3:
            mvprintw(3,21,"Major Skills: One-handed, Two-handed, Medium/Heavy Armor");
            mvprintw(4,21,"Skills/Level: 4 + Int mod");
            mvprintw(5,21,"Alignment: Lawful Good");
            mvprintw(6,21,"Hit Die: d10");

            mvprintw(20,1,"Paladins serve as beacons for their allies within the chaos of battle. While\n deadly opponents of evil, they can also empower goodly souls to aid in their\n crusades. Their magic and martial skills also make them well suited to\n defending others and blessing the fallen with the strength to continue fighting");
            break;
        case 4:
            break;
        }
        refresh();
        ch = getch();
        switch (ch) {
        case KEY_UP:
            if(selection>0)
                selection-=1;
            break;
        case KEY_DOWN:
            if(selection<6)
                selection+=1;
            break;
        case 10:
            switch(selection) {
            case 1://fighter
            case 3://paladin
                characters[0].set_skill_level("One-handed",14);
                characters[0].set_skill_level("Two-handed",5);
                characters[0].set_skill_level("Medium",5);
                characters[0].set_skill_level("Heavy",5);
                PLAYER.inventory.emplace_back("base.weapon.short_sword","base.material.iron","",100);
                creation_appearance();
                break;
            case 2://monk
                characters[0].set_skill_level("Light",5);
                characters[0].set_skill_level("Unarmored",5);
                characters[0].set_skill_level("Unarmed",5);
                creation_appearance();
                break;
            }
            break;
        }
    }
}

void Menu::creation_appearance() {
    //gender, name, age, height, skin color, hair color, eye color
    bool gender=0;
    string name = "Adventurer";
    int values_min[] = {g_age_min,g_height_min,0,0,0};
    int values[] = {18,70,0,0,0};//age,height,skin color, hair color, eye color
    int values_max[] = {g_age_max,g_height_max,11,8,5};
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    string options[] = {"Gender","Name","Age","Height","Skin Color","Hair Color","Eye Color"};
    int ch;
    unsigned short selection = 0;
    while(true) {
        move(1,0);
        clrtobot();
        mvprintw(2,0," Customize your character");

        //mvprintw(11,3,"<press enter to continue>");

        for(int i=0; i<8; i++){
            if(i!=7)
                mvprintw(3+i,3,"%s ",&options[i][0]);
            else
                move(4+i,3);
            if(selection==i)
                attron(COLOR_PAIR(1));
            printw("< ");
            if(i==0){
                if(gender)
                    printw("male");
                else
                    printw("female");
            }
            else if(i==1)
                printw("%s",&name[0]);
            else if(i<4)
                printw("%i",values[i-2]);
            else if(i==4)
                printw("%s",&g_names_colors_skin[values[i-2]][0]);
            else if(i==5)
                printw("%s",&g_names_colors_hair[values[i-2]][0]);
            else if(i==6)
                printw("%s",&g_names_colors_eye[values[i-2]][0]);
            else if(i==7)
                printw("CONTINUE");
            printw(" >");
            if(selection==i)
                attroff(COLOR_PAIR(1));
        }

        switch(selection) {
        case 1:
            break;
        case 2:
            break;
        case 4:
            break;
        case 0:
            break;
        }
        refresh();
        ch = getch();
        switch (ch) {
        case 10://enter
            if(selection==7){
                characters[0].set_name(name);
                characters[0].set_age(values[0]);
                characters[0].set_height(values[1]);
                characters[0].set_skin_color(values[2]);
                characters[0].set_hair_color(values[3]);
                characters[0].set_eye_color(values[4]);
                if(gender){
                    characters[0].has_penis=false;
                    characters[0].has_vagina=true;
                }else{
                    characters[0].has_penis=true;
                    characters[0].has_vagina=false;
                }
                g_game_active=1;
                clear();
                drawer.init();
                controller.movement();
            }else if(selection==1){
                move(4,10);
                clrtoeol();
                attron(COLOR_PAIR(1));
                name="";
                mvprintw(4,10,&name[0]);
                printw("_ >");
                refresh();
                while(true){
                    ch = getch();
                    if(ch==10){
                        if(!name.compare(""))
                            name="Adventurer";
                        break;
                    }
                    if(ch==8){
                        if(name.size()>0)
                            name.pop_back();
                    }
                    else if((ch>64&&ch<91)||(ch>96&&ch<123)){
                        if(name.size()<10)
                            name.push_back(ch);
                    }
                    if(name.size()<10){
                        mvprintw(4,10,"%s_",&name[0]);
                    }else if(name.size()==10){
                        mvprintw(4,10,"%s",&name[0]);
                    }
                    printw(" >");
                    clrtoeol();
                    refresh();
                }
                attroff(COLOR_PAIR(1));
            }
            break;
        case KEY_UP:
            if(selection>0)
                selection-=1;
            break;
        case KEY_DOWN:
            if(selection<7)
                selection+=1;
            break;
        case KEY_LEFT:
            if(selection==0)
                gender=(!gender);
            else if(selection!=1){
                if(values[selection-2]>values_min[selection-2])
                    values[selection-2]-=1;
                else
                    values[selection-2]=values_max[selection-2];
            }
            break;
        case KEY_RIGHT:
            if(selection==0)
                gender=(!gender);
            else if(selection!=1){
                if(values[selection-2]<values_max[selection-2])
                    values[selection-2]+=1;
                else
                    values[selection-2]=values_min[selection-2];
            }
            break;
        }
    }
}

int Menu::print_options(int args,int print_loc_x,int print_loc_y,int start_index,std::string options[]) {
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    int ch;
    unsigned short selection = start_index;
    while(true) {
        for(int i=0; i<args; i++)
            mvprintw(print_loc_x+i,print_loc_y,"|%s",&options[i][0]);
        attron(COLOR_PAIR(1));
        mvprintw(print_loc_x+selection,print_loc_y,"|%s",&options[selection][0]);
        attroff(COLOR_PAIR(1));
        refresh();
        ch = getch();
        switch (ch) {
        case KEY_UP:
            if(selection>0)
                selection-=1;
            break;
        case KEY_DOWN:
            if(selection<args-1)
                selection+=1;
            break;
        case 10:
            return selection;
        }
    }
}
Menu::Menu() {
}

Menu::~Menu() {
    //dtor
}
