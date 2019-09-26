#ifndef GAME_HANDLER
#define GAME_HANDLER

#include "SDL.h"

class LuaContext;

class player;

class map;

class camera;

class tilemap;

class eventHandler;

class game {
public:
    void handle_game(camera *, const Uint8 *, map *);

    void handle_game(const Uint8 *key, camera *, tilemap *);

    void handle_game(const Uint8 *key, camera *, tilemap *, player *, LuaContext *, eventHandler *);

    game();
};

#endif
