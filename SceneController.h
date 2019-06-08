#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H
#include "Mapper.h"

class SceneController
{
    public:
        SceneController();
        virtual ~SceneController();
        void movement();
        void encounter();
        void inventory();
        void equipment();
        void equip_item(int selection);
        void inspect_item(int prev,int selection);
        void inspect_character(int passed_id);
        void inspect_character_skills(int passed_id);
        void g_mode_debug_menu();
        int get_input();
    protected:

    private:
};

#endif // SCENECONTROLLER_H
