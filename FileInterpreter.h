#ifndef FILEINTERPRETER_H
#define FILEINTERPRETER_H
#include <vector>
#include <string>

class FileInterpreter
{
    public:
        FileInterpreter();
        virtual ~FileInterpreter();
        void init();
    protected:

    private:
        std::vector<std::string> read_folder(std::string folder);
        bool check_bool(int check);
        void load_settings();
        void find_modules();
        void load_module_load_order();
};

#endif // FILEINTERPRETER_H
