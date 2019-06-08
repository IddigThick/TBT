#ifndef MAPER_H
#define MAPER_H
#include "Tile.h"
#include "Map.h"
#include <vector>


class Maper
{
    public:
        Maper();
        virtual ~Maper();

    protected:
        vector<Map> maps;
    private:
        void print(int map_id);
};

#endif // MAPER_H
