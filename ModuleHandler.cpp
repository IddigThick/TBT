#include "ModuleHandler.h"
#include <fstream>//read files
#include <iostream>//g_mode_debug printing
#include <array>
#include "Global.h"

using namespace std;

void ModuleHandler::load_module(std::string module_id,int module_index){
    if(g_mode_debug)
        cout << "~LOADING MODULE "<<module_id<<"~\n";
    load_weapons(module_id,module_index);
    load_materials(module_id,module_index);
}
void ModuleHandler::load_weapons(std::string module_id,int module_index){
    int weapon_index=-1;
    string value = "";
    string parameter = "";
    string line;

    vector<Weapon> weapons;
    vector<string> classes;

    vector<string> output = {"0","0","0","0","0","0","0"};
    array<string,6> parameters = {"weapon_id","name","weight","damage","value","one_handed"};

    if(g_mode_debug)
        cout << "~LOADING WEAPONS FROM "<<module_id<<"~\n";
    ifstream inFile("modules/"+module_id+"/weapons.txt");
    ofstream outFile;
    if(inFile){//if there is a settings file
        while (getline(inFile,line)) {//while (inFile >> line), to end at each space
            //if the line exists, the line has not been commented out, and it follows the format variable_name=x
            if(line.compare("")&&line.substr(0,2).compare("//")&&line.find('=')!=string::npos&&(line.substr(line.find('=')+1,line.size()-1)).compare("")){
                parameter = line.substr(0,line.find('='));
                value=line.substr(line.find('=')+1,line.size()-1);
                for(unsigned short i=0;i<parameters.size();i++){
                    if(!parameter.compare(parameters[i])){
                        if(!parameter.compare("weapon_id")){
                            weapon_index+=1;
                            if(weapon_index!=0){
                                weapons.emplace_back(output[0],output[1],stod(output[2]),stod(output[3]),stod(output[4]),stoi(output[5]),classes);
                                if(g_mode_debug)
                                    cout << "  loaded: " << module_id+".weapon."+output[0] << endl;
                                classes.clear();
                            }
                        }
                        if(!parameter.compare("classes")){
                            while(line.find(',')!=string::npos){
                                classes.push_back(line.substr(0,line.find(',')));
                                line=line.substr(line.find(',')+1,line.size()-1);
                            }
                            classes.push_back(line);
                        }else
                            output[i]=value;
                    }
                }
                if(g_mode_debug)
                    cout << "   " << line << " -> " << parameter << "," << value << endl;
            }else if(line.compare("")&&line.substr(0,2).compare("//")&&line.find('=')!=string::npos&&!((line.substr(line.find('=')+1,line.size()-1)).compare(""))){
                parameter = line.substr(0,line.find('='));
                if(g_mode_debug)
                    cout << "**ERROR - no value for parameter \"" << parameter << "\"**" << endl;
            }
        }
        inFile.close();
        module_weapons.push_back(weapons);
    }else
        if(g_mode_debug)
            cout << "??no weapons found??";
}
void ModuleHandler::load_materials(std::string module_id,int module_index){
    int material_index=-1;
    string value = "";
    string parameter = "";
    string line;

    vector<Material> materials;
    //vector<string> classes;

    vector<string> output = {"0","0","0","0","0","0","0","0","0","0","0"};
    array<string,11> parameters = {"material_id","name","weight","damage","armor","value","rarity","difficulty","weapon_safe","armor_safe","metal"};

    if(g_mode_debug)
        cout << "~LOADING MATERIALS FROM "<<module_id<<"~\n";
    ifstream inFile("modules/"+module_id+"/materials.txt");
    ofstream outFile;
    if(inFile){//if there is a settings file
        while (getline(inFile,line)) {//while (inFile >> line), to end at each space
            //if the line exists, the line has not been commented out, and it follows the format variable_name=x
            if(line.compare("")&&line.substr(0,2).compare("//")&&line.find('=')!=string::npos&&(line.substr(line.find('=')+1,line.size()-1)).compare("")){
                parameter = line.substr(0,line.find('='));
                value=line.substr(line.find('=')+1,line.size()-1);
                for(unsigned short i=0;i<parameters.size();i++){
                    if(!parameter.compare(parameters[i])){
                        if(!parameter.compare("material_id")){
                            material_index+=1;
                            if(material_index!=0){
                                materials.emplace_back(output[0],output[1],stod(output[2]),stod(output[3]),stod(output[4]),stod(output[5]),stoi(output[6]),stoi(output[7]),stoi(output[8]),stoi(output[9]),stoi(output[10]));
                                if(g_mode_debug)
                                    cout << "  loaded: " << module_id+".material."+output[0] << endl;
                                //classes.clear();
                            }
                        }
                        /*might use to load tags
                        if(!parameter.compare("classes")){
                            while(line.find(',')!=string::npos){
                                classes.push_back(line.substr(0,line.find(',')));
                                line=line.substr(line.find(',')+1,line.size()-1);
                            }
                            classes.push_back(line);
                        }else
                            output[i]=value;
                        */
                        output[i]=value;
                    }
                }
                if(g_mode_debug)
                    cout << "   " << line << " -> " << parameter << "," << value << endl;
            }else if(line.compare("")&&line.substr(0,2).compare("//")&&line.find('=')!=string::npos&&!((line.substr(line.find('=')+1,line.size()-1)).compare(""))){
                parameter = line.substr(0,line.find('='));
                if(g_mode_debug)
                    cout << "**ERROR - no value for parameter \"" << parameter << "\"**" << endl;
            }
        }
        inFile.close();
        module_materials.push_back(materials);
    }else
        if(g_mode_debug)
            cout << "??no materials found??";
}
void ModuleHandler::init(){
    cout << "~START ModuleHandler INIT~\n";
    for(unsigned short i=0;i<g_load_order.size();i++)
        load_module(g_load_order[i],i);
    cout << "~END ModuleHandler INIT~\n";
    if(g_mode_debug){
        cout << "\npress any key to continue..." << endl;
        cin.get();
    }
}
string ModuleHandler::get_item_name(string passed_item){
    //passed_item = base.weapon.short_sword
    int module_index=-1;
    string item;
    //search for passed_item's module index
    for(unsigned short i=0;i<g_load_order.size();i++)
        if(!g_load_order[i].compare(passed_item.substr(0,passed_item.find('.')))){
            module_index=i;
            break;
        }
    //if the module couldn't be found
    if(module_index==-1)
        return "MISSING_MODULE";
    //remove module name from passed_item
    passed_item=passed_item.substr(passed_item.find('.')+1,passed_item.size()-1);
    //if the item is a weapon
    if(!passed_item.substr(0,passed_item.find('.')).compare("weapon")){
        //remove type from passed_item
        passed_item=passed_item.substr(passed_item.find('.')+1,passed_item.size()-1);
        for(unsigned short i=0;i<module_weapons[module_index].size();i++){
            if(!module_weapons[module_index][i].weapon_id.compare(passed_item))
                return module_weapons[module_index][i].name;
            /*
            if(!module_weapons[module_index][i][0].compare(passed_item))//if the ID matches
                return module_weapons[module_index][i][1];//return the name
            */
        }
    }
    return "ERROR";
}
string ModuleHandler::get_material_name(string passed_material){
    //passed_material = base.material.iron
    int module_index=-1;
    string item;
    //search for passed_item's module index
    for(unsigned short i=0;i<g_load_order.size();i++)
        if(!g_load_order[i].compare(passed_material.substr(0,passed_material.find('.')))){
            module_index=i;
            break;
        }
    //if the module couldn't be found
    if(module_index==-1)
        return "MISSING_MODULE";
    //remove module name from passed_material
    passed_material=passed_material.substr(passed_material.find('.')+1,passed_material.size()-1);
    //remove material from passed_material
    passed_material=passed_material.substr(passed_material.find('.')+1,passed_material.size()-1);
    for(unsigned short i=0;i<module_materials[module_index].size();i++){
        if(!module_materials[module_index][i].material_id.compare(passed_material))
            return module_materials[module_index][i].name;
        /*
        if(!module_weapons[module_index][i][0].compare(passed_item))//if the ID matches
            return module_weapons[module_index][i][1];//return the name
        */
    }
    return "ERROR";
}
Item ModuleHandler::generate_random_weapon(){
    int total_weapons = 0;
    for(unsigned short i=0;i<module_weapons.size();i++){
        total_weapons+=module_weapons[i].size();
    }
    unsigned short selected_weapon = (rand() % total_weapons);
    string weapon_id;
    int stored_total_weapons=total_weapons;
    total_weapons=0;
    for(unsigned short i=0;i<module_weapons.size();i++){
        if(selected_weapon<module_weapons[i].size())
            weapon_id=g_load_order[i]+".weapon."+module_weapons[i][selected_weapon].weapon_id;
        else
            selected_weapon-=module_weapons[i].size();
    }

    int total_materials;
    int stored_total_materials;
    unsigned short selected_material;
    string material_id;
    bool flag=true;
    while(flag){
        total_materials = 0;
        for(unsigned short i=0;i<module_materials.size();i++){
            total_materials+=module_materials[i].size();
        }
        selected_material = (rand() % total_materials);
        stored_total_materials=total_materials;
        total_materials=0;
        for(unsigned short i=0;i<module_materials.size();i++){
            if(selected_material<module_materials[i].size()){
                if(module_materials[i][selected_material].weapon_safe){
                    material_id=g_load_order[i]+".material."+module_materials[i][selected_material].material_id;
                    flag=false;
                }
                else
                    break;
            }
            else
                selected_material-=module_materials[i].size();
        }
    }

    mvprintw(2,13,"Total Weapons:%i   | Total Materials:%i",stored_total_weapons,stored_total_materials);
    mvprintw(3,13,"Selected Weapon:%i | Selected Material:%i",selected_weapon,selected_material);

    refresh();
    Item temp(weapon_id,material_id,"",100);
    return temp;
}
int ModuleHandler::get_equipment_type(string passed_item){
    return -1;
}
ModuleHandler::ModuleHandler()
{
    //ctor
}

ModuleHandler::~ModuleHandler()
{
    //dtor
}
