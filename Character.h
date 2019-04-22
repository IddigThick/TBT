#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>//strings

using namespace std;

class Character {
    string name;
  public:
    //constructors
    Character();//default > generate a completely random Character
    Character(string);//generate a Character based upon preset as defined by string
    Character(int,int,int);//generate a Character based a few basic stats
    ~Character() {}
    //misc functions
    void printCharacterInfo();

    //functions to set variables
    void set_name(string passed_name);
    void set_age(int passed_age);
    void set_height(int passed_height);
    void set_health(int passed_health);
    void change_health(int passed_change);

    //functions to access every variable stored by class
    string get_name();
    unsigned short get_age();
    unsigned short get_height();
    unsigned short get_level();
    unsigned short get_gold();
    //array get functions
    unsigned short get_max_health();
    unsigned short get_health();
    unsigned short get_max_stamina();
    unsigned short get_stamina();
    unsigned short get_max_mana();
    unsigned short get_mana();
    unsigned short get_max_lust();
    unsigned short get_lust();
    unsigned short get_max_experience();
    unsigned short get_experience();

  private:


    unsigned short age;
    unsigned short height;
    unsigned short weight;

    unsigned short status_data [10];//max_health,health,max_stamina,stamina,max_mana,mana,max_lust,lust,max_experience,experience
    unsigned short level;
    unsigned short corruption;
    unsigned short gold;



    void generate_full_random();
};

#endif // CHARACTER_H
