//standard libraries
#include <iostream>//cin, cout FOR DEBUG, PLEASE REMOVE
#include <string>//strings
#include <vector>//vectors
#include <stdlib.h>//rand()
#include <math.h>//round()
//external libraries
#include "curses/curses.h"//formatted printing to console
//user libraries
#include "Global.h"
#include "Character.h"
#include "Drawer.h"

using namespace std;


/*
class Player_setup {
    public:
    private:
        unsigned short age;
        unsigned short height;
        unsigned short weight;

        void
};
*/




int main() {
    string Name;
    int Age;
    float Height;
    Character *f1;
    for (int n=0; n<3; n++) {
        /*
        cout <<"Enter name :"<<endl;
        getline(cin, Name);
        cout <<"Enter age :"<<endl;
        cin >> Age;
        cout <<"Enter height :"<<endl;
        cin>> Height;
        */
        f1 = new Character("random");
        /*
        f1->setName(Name);
        f1->setAge(Age);
        f1->setHeight(Height);
        */
        characters.push_back(*f1);
        //cin.get(); //clear buffer
    }
    //Drawer draw;
    Character player = *characters.begin();
    player.printCharacterInfo();
    //f1 = new Character;
    //characters.push_back(*f1);
    //cin.get();
    // Now setup an iterator loop through the vector

    //DEBUG - generate and display characters of random Characters
    vector<Character>::iterator it;
    for ( it = characters.begin(); it != characters.end(); ++it ) {
        it->printCharacterInfo();
    }
    cin.get();

    player.set_name("Player");

    //end Character testing///////////////////////////////////////////////////////////////////

    //screen drawing
    char users_name[ 100 ];
    Drawer draw;
    //end screen drawing ////////////////////////////////////////////////////////////////////


    //printw( "\n\n\nPress ENTER to quit." );

    getnstr( users_name, sizeof( users_name ) - 1 );

    //cout << "END PROGRAM 1";
    //exit (EXIT_FAILURE);
    //cout << "END PROGRAM";



    return 0;
}

