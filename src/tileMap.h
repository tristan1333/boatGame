#ifndef TILEMAPS___
#define TILEMAPS___

#include <string>

class tile;

class LuaContext;

class tilemap {
public:
    tile ***tiles;
    int w, h;

    tilemap(int, int);

    tilemap();

    tilemap(std::string);
};

void savTileMap(tilemap *mp);

void init_lua_map(tilemap *, LuaContext *);

#endif
