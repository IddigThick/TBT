#ifndef COMBAT_H
#define COMBAT_H
#include "Character.h"
#include "Global.h"


class Combat {
  public:
    Combat(int passed_id, int encounter_type);
    virtual ~Combat();
    void main();
    void player_turn();
    void enemy_turn();
    void victory();
    void defeat();
  protected:

  private:
    int enemy_id;
    Character *target;
};

#endif // COMBAT_H
