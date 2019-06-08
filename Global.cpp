#include "Global.h"
//g_variable_name denotes a global variable

//player settings - TODO load these parameters from config file at launch if exists,otherwise create config with default values
bool g_mode_shota=0;
bool g_mode_sfw=1;//if false,remove all NSFW scenes,you may still be beaten through lust damage. Currently: disables the display of NSFW information in character inspection
bool furry_mode=1;//TODO - if false,change every furry character to a human. This means your world will contain no cat,dog,horse,etc. morphs or the original race. Currently: does nothing
bool g_mode_debug=0;
unsigned short g_age_max=50;
unsigned short g_age_min=12;
unsigned short g_height_max=96;//remove?
unsigned short g_height_min=48;//remove?
unsigned short g_starting_ability_points=15;

//cant be modified by players
bool g_in_combat=0;
bool g_game_active=0;
bool g_aggressive_settings=1;
const unsigned short g_print_lines=17;
const unsigned short g_print_length=54;
vector<string> g_modules;
vector<string> g_load_order;

//NAMES
//body part colors
const string g_names_colors_hair[9] ={"white","blonde","dirty blonde","ginger","brown","dark brown","auburn","gray","black"};
const string g_names_colors_eye[6] ={"brown","blue","amber","hazel","green","gray"};
const string g_names_colors_skin[12] ={"pale","light","fair","porcelain","rosy","olive","tanned","dark","chocolate","ebony","mahogany","russet"};
//skill names
const string g_names_skills[25] = {"Thieving","Spellcraft","Athletics","Survival","Perception","Heavy","Medium","Light","Unarmored","One-handed","Two-handed","Ranged","Unarmed","Abjuration","Conjuration","Divination","Enchantment","Evocation","Illusion","Necromancy","Transmutation","Alchemy","Armorsmith","Weaponsmith"};
const string g_names_skill_levels[16] = {"Untrained","Dabbling","Competent","Skilled","Proficient","Talented","Adept","Expert","Professional","Accomplished","Great","Master","High Master","Grand Master","Legendary"};
//class names
const string g_names_classes_major[5] = {"fighter","archer","rogue","brawler","apprentice"};
const string g_names_classes_prestiege_fighter[3] = {"paladin","barbarian","knight"};
const string g_names_classes_prestiege_archer[3] = {"bard","ranger","hunter"};
const string g_names_classes_prestiege_rogue[3] = {"assassin","night-blade","saboteur"};
const string g_names_classes_prestiege_brawler[2] = {"monk","pugilist"};
const string g_names_classes_prestiege_apprentice[3] = {"wizard","summoner","druid"};
/*descriptors TODO - complete and implement
const string g_names_face_types[2] = {"Pretty,ugly"};
const string g_names_skin_types_good[11] = {"clear","perfect","delicate","dimpled","silky","soft","unblemished","unwrinkled","milky","youthful","pretty"};
const string g_names_skin_types_bad[8] = {"scarred","rough","waxen","scabrous","blemished","cracked","splotchy","veiny"};
const string g_names_skin_types_old[9] = {"lined","wrinkled","wrinkly","aged","leathery","loose","weathered","worn","damaged"};
const string g_names_eye_types[9] = sunken, {"eager", "watchful", "downcast", "tired", "curious", "dull", "innocent", "beady", "narrow"};
*/
//character names
const string g_names_archaic_male [271] = {"Aaryn","Aaro","Aarus","Abramus","Abrahm","Abyl","Abelus","Adannius","Adanno","Aedam","Adym","Adamus","Aedrian","Aedrio","Aedyn","Aidyn","Aelijah","Elyjah","Aendro","Androe","Aenry","Hynroe","Hynrus","Aethan","Aethyn","Aevan","Evyn","Evanus","Alecks","Alyx","Alexandyr","Xandyr","Alyn","Alaen","Andrus","Aendrus","Anglo","Aenglo","Anglus","Antony","Antonyr","Astyn","Astinus","Axelus","Axyl","Benjamyn","Benjamyr","Braidyn","Brydus","Braddeus","Brandyn","Braendyn","Bryus","Bryne","Bryn","Branus","Caeleb","Caelyb","Caerlos","Carlus","Cameryn","Camerus","Cartus","Caertero","Charlus","Chaerles","Chyrles","Christophyr","Christo","Chrystian","Chrystan","Connorus","Connyr","Daemian","Damyan","Daenyel","Danyel","Davyd","Daevo","Dominac","Dylaen","Dylus","Elius","Aeli","Elyas","Helius","Helian","Emilyan","Emilanus","Emmanus","Emynwell","Ericus","Eryc","Eryck","Ezekius","Zeckus","Ezekio","Ezrus","Yzra","Gabrael","Gaebriel","Gael","Gayl","Gayel","Gaeus","Gavyn","Gaevyn","Goshwa","Joshoe","Graysus","Graysen","Gwann","Ewan","Gwyllam","Gwyllem","Haddeus","Hudsyn","Haesoe","Haesys","Haesus","Handus","Handyr","Hantus","Huntyr","Haroldus","Haryld","Horgus","Horus","Horys","Horyce","Hosea","Hosius","Iaen","Yan","Ianus","Ivaen","Yvan","Jaecoby","Jaecob","Jaeden","Jaedyn","Jaeremiah","Jeremus","Jasyn","Jaesen","Jaxon","Jaxyn","Jaxus","Johnus","Jonus","Jonaeth","Jonathyn","Jordus","Jordyn","Josaeth","Josephus","Josaeus","Josayah","Jovanus","Giovan","Julyan","Julyo","Jyck","Jaeck","Jacus","Kaevin","Kevyn","Vinkus","Laevi","Levy","Levius","Landyn","Laendus","Leo","Leonus","Leonaerdo","Leonyrdo","Lynardus","Lincon","Lyncon","Linconus","Logaen","Logus","Louis","Lucius","Lucae","Lucaen","Lucaes","Lucoe","Lucus","Lyam","Maeson","Masyn","Maetho","Mathoe","Matteus","Matto","Maxus","Maximus","Maximo","Maxymer","Mychael","Mygwell","Miglus","Mythro","Mithrus","Naemo","Naethyn","Nathanus","Naethynel","Nicholaes","Nycholas","Nicholys","Nicolus","Nolyn","Nolanus","Olivyr","Alivyr","Olivus","Oscarus","Oscoe","Raen","Ryn","Robertus","Robett","Bertus","Romyn","Romanus","Ryderus","Ridyr","Samwell","Saemuel","Santegus","Santaegus","Sybasten","Bastyen","Tago","Aemo","Tagus","Theodorus","Theodus","Thaeodore","Thomys","Thomas","Tommus","Tylus","Tilyr","Uwyn","Oewyn","Victor","Victyr","Victorus","Vincynt","Vyncent","Vincentus","Wyttus","Wyaett","Xavius","Havius","Xavyer","Yago","Tyago","Tyego","Ysaac","Aisaac","Ysaiah","Aisiah","Siahus","Zacharus","Zachar","Zachaery"};
const string g_names_archaic_female [153] = {"Abigayl","Aebria","Aeobreia","Breia","Aedria","Aodreia","Dreia","Aeliya","Aliya","Aella","Aemilya","Aemma","Aemy","Amy","Ami","Aeria","Arya","Aeva","Aevelyn","Evylann","Alaexa","Alyxa","Alina","Aelina","Aelinea","Allisann","Allysann","Alyce","Alys","Alysea","Alyssia","Aelyssa","Amelya","Maelya","Andreya","Aendrea","Arianna","Aryanna","Arielle","Aryell","Ariella","Ashlena","Aurora","Avaery","Avyrie","Bella","Baella","Brooklinea","Bryanna","Brynna","Brinna","Caemila","Chloe","Chloeia","Claira","Clayre","Clayra","Delyla","Dalyla","Elisybeth","Aelisabeth","Ellia","Ellya","Elyana","Eliana","Eva","Falyne","Genaesis","Genaesys","Gianna","Jianna","Janna","Graece","Grassa","Haenna","Hanna","Halya","Harperia","Peria","Hazyl","Hazel","Jasmyne","Jasmine","Jocelyne","Joceline","Celine","Kaelia","Kaelya","Kathryne","Kathrine","Kayla","Kaila","Kymber","Kimbera","Layla","Laylanna","Leia","Leya","Leah","Lilia","Lylia","Luna","Maedisa","Maelania","Melania","Maya","Mya","Myla","Milae","Naomi","Naome","Natalya","Talya","Nathylie","Nataliae","Thalia","Nicola","Nikola","Nycola","Olivya","Alivya","Penelope","Paenelope","Pynelope","Rianna","Ryanna","Ruby","Ryla","Samaentha","Samytha","Sara","Sarah","Savannia","Scarletta","Sharlotta","Caerlotta","Sophya","Stella","Stylla","Valentyna","Valerya","Valeria","Valia","Valea","Victorya","Vilettia","Ximena","Imaena","Ysabel","Zoe","Zoeia","Zoea","Zoesia"};
//characters vector
vector<Character> characters = {Character("random")};

//Global functions
Mapper mapper;
Drawer drawer;
SceneController controller;
Menu menu;
FileInterpreter fileInterpreter;
ModuleHandler moduleHandler;



