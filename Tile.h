#ifndef TILE_H
#define TILE_H
#include <vector>//allow this object to store items
#include <memory>//smart vector

class Tile
{
    public:
        Tile();
        Tile(int);
        virtual ~Tile();
        bool tile_accessible;//can player go here? determined by tile_type
        //TODO - should probly be protected
        //vector<shared_ptr<Item>> items;//same as inventory vector on player
        std::vector<int> characters_here;//stores x of characters[x], stores only index, not actual character object, does NOT store player
        char tile_symbol;//what symbol the drawer will print to the screen, determined by tile_type
        std::string tile_name;
        //void get_tile_type;
        void add_character(int character_id);
        void remove_character(int character_id);
        //void add_item(Item*);
        void remove_item();
    protected:
        int tile_type;//forest,street,etc
    private:
};

#endif // TILE_H
