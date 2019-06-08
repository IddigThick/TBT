#ifndef GLOBAL_H
#define GLOBAL_H

#include <vector>
#include "Character.h"//create character
//single instance objects
#include "Mapper.h"
#include "Drawer.h"
#include "SceneController.h"
#include "Menu.h"
#include "FileInterpreter.h"
#include "ModuleHandler.h"
//definitions
#define PLAYER characters[0]

extern std::vector<Character> characters;
extern bool g_mode_shota;
extern bool g_in_combat;
extern bool g_mode_sfw;
extern bool g_mode_debug;
extern bool g_game_active;
extern bool g_aggressive_settings;
extern unsigned short g_age_max;
extern unsigned short g_age_min;
extern unsigned short g_height_max;//remove?
extern unsigned short g_height_min;//remove?
extern unsigned short g_starting_ability_points;
extern const unsigned short g_print_lines;
extern const unsigned short g_print_length;
extern std::vector<string> g_modules;
extern std::vector<string> g_load_order;
extern const string g_names_colors_hair[9];
extern const string g_names_colors_eye[6];
extern const string g_names_colors_skin[12];
extern const string g_names_skills [25];
extern const string g_names_skill_levels[16];
extern const string g_names_classes_major[5];
extern const string g_names_classes_prestiege_fighter[3];
extern const string g_names_classes_prestiege_archer[3];
extern const string g_names_classes_prestiege_rogue[3];
extern const string g_names_classes_prestiege_brawler[2];
extern const string g_names_classes_prestiege_apprentice[3];
extern const string g_names_archaic_male [271];
extern const string g_names_archaic_female [153];
//extern Character* player;
extern Mapper mapper;
extern Drawer drawer;
extern SceneController controller;
extern Menu menu;
extern FileInterpreter fileInterpreter;
extern ModuleHandler moduleHandler;

#endif
