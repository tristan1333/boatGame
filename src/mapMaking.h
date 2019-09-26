#ifndef MP_MK_DEF__
#define MP_MK_DEF__

#include <string>
#include <vector>

class LuaContext;

class SDL_Rect;

class SDL_Point;

class tileInventory;

class camera;

class tilemap;

class mapMakeHandler {
public:
    std::string saved_tiles[6];


    tileInventory *inventory;

    void handle(camera *, tilemap *);

    mapMakeHandler(LuaContext *);
};

class tileInventory {
public:
    std::vector<std::string> tiles;
    std::string curr_tile;
    bool show;

    bool showInv();

    std::vector<SDL_Rect *> clickboxes;

    void checkClickCollison(SDL_Point);

    int curr_point;

    void activate(int);

    void displayInventory();

    tileInventory(LuaContext *);
};

#endif