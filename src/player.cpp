#include "camera.h"
#include "player.h"
#include "load_textures.h"
#include "tiles.h"
#include "tileMap.h"
#include "hitbox.h"
#include <iostream>
#include "LuaContext.hpp"

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
int ticks_per_frame = 1000 / 60;
double move_speed = .7;
extern std::vector<SDL_Texture *> textures;
extern std::unordered_map<std::string, SDL_Texture *> tex;

player::player() {
    this->pos = new Vec2(5, 5);
    this->w = .5;
    this->h = .5;
    this->mv_speed = .003;
    this->hbox = new hitbox(0, 0, w, h);
}

void callOnEnter(int x, int y, float lx, float ly, tilemap *mp, LuaContext *L, int dir) {
    std::string execCod =
            "tiles.reg['" + mp->tiles[x][y]->type->id + "']:onEnter(" + std::to_string(x) + ", " + std::to_string(y) +
            ", " + std::to_string(lx) + ", " + std::to_string(ly) + ", " + std::to_string(dir) + ")";
    //std::cout << execCod << std::endl;
    L->executeCode(execCod);
}

float player::grabHitBoxLeftX() {
    return this->pos->x + hbox->x;
}

float player::grabHitBoxRight() {
    return this->pos->x + hbox->x + this->hbox->w;
}

float player::grabHitBoxBottom() {
    return this->pos->y + hbox->y + this->hbox->h;
}

float player::grabHitBoxTop() {
    return this->pos->y + hbox->y;
}

void player::move(float xmv, float ymv, tilemap *mp, LuaContext *L) {
    int origTilex = grabHitBoxLeftX();
    int origTileRx = grabHitBoxRight();
    int origTiley = grabHitBoxTop();
    int origTileBy = grabHitBoxBottom();
//	std::cout << "starting at" << (int)this->pos->x;
    this->pos->x += xmv * ticks_per_frame;
    this->pos->y += ymv * ticks_per_frame;
    std::string execCode = std::string(
            "player:setPos(" + std::to_string(this->pos->x) + ", " + std::to_string(this->pos->y) + ")");

    //std::cout << execCode;
//	L->executeCode("player:setPos(5,5)");
    L->executeCode(execCode);
    if (origTileRx < (int) (grabHitBoxRight())) {
        //	std::cout << "x " << origTilex << " to " << (int)(grabHitBoxRight()) << std::endl;
        callOnEnter((int) grabHitBoxRight(), origTiley, grabHitBoxRight(), this->pos->y, mp, L, RIGHT);
        callOnEnter(grabHitBoxRight(), origTileBy, grabHitBoxRight(), this->pos->y, mp, L, RIGHT);
        //std::cout << "Player has trespassed on tile " << bp->pos->x;
    } else if ((int) origTilex > (int) grabHitBoxLeftX()) {
        callOnEnter((int) grabHitBoxLeftX(), grabHitBoxBottom(), grabHitBoxLeftX(), origTileBy, mp, L, LEFT);
//		this->pos->x = L->readVariable<float>("player", "x");
        this->pos->y = L->readVariable<float>("player", "y");
        callOnEnter(grabHitBoxLeftX(), grabHitBoxTop(), grabHitBoxLeftX(), origTiley, mp, L, LEFT);
        //	tile*bp = mp->tiles[(int)(this->pos->x - 1)][(int)this->pos->y];
        //	std::cout << "x " << origTilex << " to " << (int)this->pos->x << std::endl;;
    } else if ((int) origTiley > (int) this->grabHitBoxTop()) {
        //	std::cout << "y " << origTiley << " to " << (int)this->pos->y << std::endl;
        callOnEnter((int) this->pos->x, grabHitBoxTop(), origTilex, this->pos->y, mp, L, UP);
        //	this->pos->x = L->readVariable<float>("player", "x");
        //	this->pos->y = L->readVariable<float>("player", "y");
        callOnEnter(grabHitBoxRight(), grabHitBoxTop(), this->pos->x, this->pos->y, mp, L, UP);
        //	tile* bp = mp->tiles[(int)(this->pos->x)][(int)(this->pos->y + this->h)];
        //	std::cout << "Player has tresspassed on tile " << bp->pos->y;
        //std::cout << "Player has trespassed on tile " << bp->pos->x;
    } else if ((int) origTileBy < (int) (grabHitBoxBottom())) {
        //	std::cout << "y " << origTiley << " to " << (int)(this->pos->y + this->h) << std::endl;
        callOnEnter((int) this->pos->x, grabHitBoxBottom(), this->pos->x, this->pos->y + this->h, mp, L, DOWN);
        //	this->pos->x = L->readVariable<float>("player", "x");
        //	this->pos->y = L->readVariable<float>("player", "y");
        callOnEnter(grabHitBoxRight(), grabHitBoxBottom(), this->pos->x, this->pos->y + this->h, mp, L, DOWN);
    }
    this->pos->x = L->readVariable<float>("player", "x");
    this->pos->y = L->readVariable<float>("player", "y");
}

void player::handle(const Uint8 *key, tilemap *mp, LuaContext *L, camera* maincam) {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			int mousex, mousey;
			int screenw, screenh;
			SDL_GetMouseState(&mousex, &mousey);
			float nx = mousex;
			float ny = mousey;
			SDL_Point p = { mousex, mousey };
			convertToWorld(nx, ny, maincam);
			std::cout << "Player clicked " << nx << "/" << ny;
			std::string execCode = std::string(
				"clickUpdates:Add(" + std::to_string(nx) + ", " + std::to_string(ny) + ")");
			L->executeCode(execCode);
		}
	}
    if (key[SDL_SCANCODE_D]) {

        this->move(mv_speed, 0, mp, L);
    }
    if (key[SDL_SCANCODE_A]) {
        this->move(-mv_speed, 0, mp, L);
    }
    if (key[SDL_SCANCODE_W]) {
        this->move(0, -mv_speed, mp, L);
    }
    if (key[SDL_SCANCODE_S]) {
        this->move(0, mv_speed, mp, L);
    }

    std::string execCode = std::string(
            "player:setPos(" + std::to_string(this->pos->x) + ", " + std::to_string(this->pos->y) + ")");

    //std::cout << execCode;
//	L->executeCode("player:setPos(5,5)");
    L->executeCode(execCode);
}

void init_player() {
    tex["player"] = loadTexture("Resources/Base/Characters/player.png");
}