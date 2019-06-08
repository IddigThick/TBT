#include "FileInterpreter.h"
#include "Global.h"//modify global vars
#include <windows.h>//allow folder discovery TODO - replace with cross-platform solution
#include <fstream>//read files
#include <iostream>//g_mode_debug printing

using namespace std;

vector<string> FileInterpreter::read_folder(string folder)
{
    vector<string> names;
    string search_path = folder + "/*.*";
    WIN32_FIND_DATA file;
    HANDLE search_handle = FindFirstFile(search_path.c_str(), &file);
    if(search_handle != INVALID_HANDLE_VALUE) {
        do {
            names.push_back(file.cFileName);
        }while(FindNextFile(search_handle, &file));
        FindClose(search_handle);
    }
    return names;
}
bool FileInterpreter::check_bool(int check){
    if(check==1||check==0)
        return true;
    if(g_mode_debug)
        cout << "**ERROR - set to non-boolean value, using default value**\n";
    return false;
}
void FileInterpreter::find_modules(){
    string line;
    string parameter;
    string value;
    ifstream inFile;
    if(g_mode_debug)
        cout << "~LOADING MODULES~\n";
    vector<string> names = read_folder("modules");
    if(g_mode_debug)
        cout << "Found module folders: ";
    for(unsigned short i=2;i<names.size();i++){
        cout << names[i] << " ";
    }
    cout << endl;
    for(unsigned short i=2;i<names.size();i++){
        if(g_mode_debug)
            cout << "Loading module "+names[i]+" PATH=[modules/"+names[i]+"/module.mod]:\n";
        inFile.open("modules/"+names[i]+"/module.mod");
        if(inFile){
            while (getline(inFile,line)){
                //if the line exists, the line has not been commented out, and it follows the format variable_name=x
                if(line.compare("")&&line.substr(0,2).compare("//")&&line.find('=')!=string::npos&&(line.substr(line.find('=')+1,line.size()-1)).compare("")){
                    parameter = line.substr(0,line.find('='));
                    value = line.substr(line.find('=')+1,line.size()-1);
                    if(g_mode_debug)
                        cout << "   " << parameter << "=" << value << endl;
                    if(!parameter.compare("module_id"))
                        g_modules.push_back(value);
                }
            }
        }else
            if(g_mode_debug)
                cout << "**ERROR - "+names[i]+" has no module.mod file!**\n";
        inFile.close();
    }
    if(g_mode_debug)
        cout << "Found modules: ";
    for(unsigned short i=0;i<g_modules.size();i++){
        if(g_mode_debug)
            cout << g_modules[i] << " ";
    }
    cout << "\n~DONE LOADING MODULES~\n\n";
}
void FileInterpreter::load_module_load_order() {
    string line;
    vector<string> load_order_file;
    if(g_mode_debug)
        cout << "~DETERMINING LOAD ORDER~\n";
    ifstream inFile("load_order.cfg");
    ofstream outFile;
    if(inFile){
        while (getline(inFile,line)){
            for(unsigned short i=0;i<g_modules.size();i++){
                if(!g_modules[i].compare(line)){
                    g_modules.erase(g_modules.begin()+i);
                    g_load_order.push_back(line);
                    break;
                }
                if(i==g_modules.size()-1)
                    if(g_mode_debug)
                        cout << "**ERROR - "+line+" no longer exists, removing from load order**\n";
            }
        }
        inFile.close();
        remove("load_order.cfg");
        outFile.open("load_order.cfg");
        for(unsigned short i=0;i<g_load_order.size();i++){
            outFile << g_load_order[i] << endl;
        }
    }else{
        if(g_mode_debug)
            cout << "load_order.cfg does not exist, generating using default settings\n" << endl;
        outFile.open("load_order.cfg");
        outFile << "base";
        g_load_order.push_back("base");
        for(unsigned short i=0;i<g_modules.size();i++)
            if(!g_modules[i].compare("base"))
                g_modules.erase(g_modules.begin()+i);
        outFile.close();
    }
    if(g_mode_debug)
        cout << "Final load order is:\n";
    for(unsigned short i=0;i<g_load_order.size();i++){
        if(g_mode_debug)
            cout << "   " << i << ": " << g_load_order[i] << endl;
    }

    if(g_mode_debug)
        cout << "\n~DONE DETERMINING LOAD ORDER~\n\n";
}
void FileInterpreter::load_settings(){
    string line;
    string parameter;
    int value=0;
    bool error_flag=0;
    cout << "~LOADING SETTINGS~\n";
    ifstream inFile("settings.cfg");
    ofstream outfile;
    if(inFile){//if there is a settings file
        while (getline(inFile,line)) {//while (inFile >> line), to end at each space
            if(line.compare("")&&line.substr(0,2).compare("//")&&line.find('=')!=string::npos&&(line.substr(line.find('=')+1,line.size()-1)).compare("")){//if the line exists, the line has not been commented out, and it follows the format variable_name=x
                parameter = line.substr(0,line.find('='));
                try{
                value = stoi(line.substr(line.find('=')+1,line.size()-1));
                }catch(invalid_argument) {//if the value for the parameter can not be converted to an int (usually because there is no value)
                    cout << "**ERROR - for parameter \"" << parameter << "\", " << "tried to convert \"" << line.substr(line.find('=')+1,line.size()-1) << "\" into an integer**" << endl;
                    error_flag=1;
                }
                cout << line << " -> " << parameter << "," << value << endl;
                if(!parameter.compare("g_mode_debug")){
                    if(check_bool(value))
                        g_mode_debug=value;
                    else
                        cout << "**ERROR - g_mode_debug set to non-boolean, value rejected**\n";
                }else if(!parameter.compare("g_mode_sfw")){
                    if(check_bool(value))
                        g_mode_sfw=value;
                    else
                        cout << "**ERROR - g_mode_sfw set to non-boolean, value rejected**\n";
                }else if(!parameter.compare("g_age_max")){
                    if(value>0&&value<SHRT_MAX)
                        g_age_max=value;
                    else
                        cout << "**ERROR - g_age_max < 0 or g_age_max > SHRT_MAX, value rejected**\n";
                }else if(!parameter.compare("g_age_min")){
                    if(value>0&&value<=g_age_max&&value<SHRT_MAX)
                        g_age_min=value;
                    else {
                        cout << "**ERROR - g_age_min < 0 or g_age_min > (g_age_max or SHRT_MAX), value rejected**\n";
                        if(g_age_min > g_age_max)
                            cout << "**ERROR - g_age_max < default g_age_min, value rejected**\n";
                    }
                }else if(!parameter.compare("g_height_max")){
                }else if(!parameter.compare("g_starting_ability_points")){
                    if(value>0&&value<SHRT_MAX)
                        g_starting_ability_points=value;
                }
            }else if(line.compare("")&&line.substr(0,2).compare("//")&&line.find('=')!=string::npos&&!((line.substr(line.find('=')+1,line.size()-1)).compare(""))){
                parameter = line.substr(0,line.find('='));
                cout << "**ERROR - no value for parameter \"" << parameter << "\"**" << endl;
            }
        }
        inFile.close();
    }
    inFile.open("settings.cfg");
    if(!inFile||(error_flag&&g_aggressive_settings)){//if there is no settings file, or theres an error with the existing file
        if(g_mode_debug)
            cout << "**ERROR - issue has been detected with settings.cfg**" << endl;
        if(g_mode_debug&&!error_flag)
            cout << "settings.cfg does not exist, generating using default settings" << endl;
        else if(g_mode_debug&&error_flag){
            if(g_mode_debug)
                cout << "!!malformed settings.cfg is being copied to settings.old!!" << endl;
            ifstream inFile("settings.cfg");
            outfile.open("settings.old");
            if(g_mode_debug)
                outfile << "//!!TBT detected an issue with this configuration!!\n";
            while (getline(inFile,line)) {
                outfile << line << endl;
            }
            outfile.close();
            if(g_mode_debug)
                cout << "!!settings.cfg is being generated using default settings!!" << endl;
        }
        inFile.close();//close the input
        outfile.open("settings.cfg");//create the file
        outfile << "//SETTINGS FOR TBT\n\n//ALWAYS overwrite entire file is error is found\ng_aggresive_settings=0\n\n//enable debug mode\ng_mode_debug=0\n\n//enable sfw mode\ng_mode_sfw=1\n\n//set max age\ng_age_max=50\n\n//set min age\ng_age_min=12\n\n//set max height\ng_height_max=96\n\n//set min height\ng_height_min=48\n\n//set ability points for character creation\ng_starting_ability_points=15";//write the default settings
        outfile.close();//close the file
    }
    cout << "~DONE LOADING SETTINGS~" << endl;

    if(error_flag){
        cout << "\npress any key to continue..." << endl;
        cin.get();
    }
}
void FileInterpreter::init(){
    cout << "~START FileInterpreter INIT~\n";
    load_settings();
    find_modules();
    load_module_load_order();
    cout << "~END FileInterpreter INIT~\n";
    if(g_mode_debug){
        cout << "\npress any key to continue..." << endl;
        cin.get();
    }
}
FileInterpreter::FileInterpreter()
{
}

FileInterpreter::~FileInterpreter()
{
    //dtor
}
