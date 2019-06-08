#ifndef MAPPER_H
#define MAPPER_H
#include "Tile.h"
#include "Map.h"
#include <vector>

class Mapper{
    public:
        Mapper();
        virtual ~Mapper();
        //TODO - should probly be private
        void print(int map_id);
        std::vector<Map> maps;
    protected:
    private:
        void g_mode_debug_add_item();

};

#endif // MAPPER_H
