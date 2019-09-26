#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"

class Vec2;

class tilemap;

class LuaContext;

class hitbox;

class player {
public:
    Vec2 *pos;
    float w;
    float h;
    float mv_speed;
    hitbox *hbox;

    float grabHitBoxLeftX();

    float grabHitBoxRight();

    float grabHitBoxBottom();

    float grabHitBoxTop();

    void handle(const Uint8 *, tilemap *, LuaContext *);

    void move(float, float, tilemap *, LuaContext *);

    player();
    //player(float,float,float,float);
};

void init_player();

#endif
