#include "load_textures.h"
#include "platform.h"
#include "map.h"
#include "timers.h"
#include "gameHandler.h"
#include "tilemap.h"
#include "tiles.h"
#include "camera.h"
#include "player.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "events.h"

const int TARGET_FPS = 60;
const double ticks_per_frame = 1000 / TARGET_FPS;
extern std::unordered_map<std::string, SDL_Texture *> tex;
extern std::vector<SDL_Texture *> textures;
SDL_Color col{200, 100, 4, 255};
SDL_Texture *text_curr;

void game::handle_game(const Uint8 *key, camera *maincam, tilemap *mp) {
    for (int x = 0; x <= mp->w; x++) {
        for (int y = 0; y <= mp->h; y++) {
            //	std::cout << tex[mp->tiles[x][y]->type->id];
            renderToWorld(mp->tiles[x][y]->pos, 1, 1, maincam, tex[mp->tiles[x][y]->type->id]); //
            //	std::cout << mp->tiles[x][y]->type->id << std::endl;
            //	std::cout << mp->tiles[x][y]->pos->x << " " << std::endl;
            //	std::cout << mp->tiles[x][y]->pos->y << std::endl;
            //	std::cout << y;
            //	std::cout << "\n";
        }
    }
    int mousex, mousey;
    int screenw, screenh;
//	SDL_GetWindowSize(mainwin, &screenw, &screenh);

    SDL_GetMouseState(&mousex, &mousey);
    float nx = mousex;
    float ny = mousey;
    convertToWorld(nx, ny, maincam);
    //convertToWorld(nx, ny);
//	std::string oss = std::to_string(nx);
    std::string oss = std::string("") + std::to_string((int) nx) + ", " + std::to_string((int) ny);
    text_curr = loadText(oss, col, nx + 5, ny + 20, 100, 100);
    SDL_DestroyTexture(text_curr);
    if (key[SDL_SCANCODE_D]) {
        maincam->camPos.x += 0.01 * ticks_per_frame;
    }
    if (key[SDL_SCANCODE_A]) {
        maincam->camPos.x -= 0.01 * ticks_per_frame;
    }
    if (key[SDL_SCANCODE_W]) {
        maincam->camPos.y -= 0.01 * ticks_per_frame;
    }
    if (key[SDL_SCANCODE_S]) {
        maincam->camPos.y += 0.01 * ticks_per_frame;
    }
    if (key[SDL_SCANCODE_N]) {
        maincam->w -= 0.01 * ticks_per_frame;
        maincam->h -= 0.01 * ticks_per_frame;
    }
    if (key[SDL_SCANCODE_M]) {
        maincam->w += 0.01 * ticks_per_frame;
        maincam->h += 0.01 * ticks_per_frame;
    }
}

void
game::handle_game(const Uint8 *key, camera *maincam, tilemap *mp, player *plr, LuaContext *L, eventHandler *events) {
    for (int y = 0; y <= 14; y++) {
        int y_pos = plr->pos->y - 7 + y;
        if (y_pos < 0 || y_pos > mp->h) {
            continue;
        }
        for (int x = 0; x <= 14; x++) {
            int x_pos = plr->pos->x - 7 + x;
            if (x_pos < 0 || x_pos > mp->w) {
                continue;
            }

            renderToWorld(mp->tiles[x_pos][y_pos]->pos, 1, 1, maincam, tex[mp->tiles[x_pos][y_pos]->type->id]);
        }
    }
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_MOUSEMOTION)
		{

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			int mousex, mousey;
			//	SDL_GetWindowSize(mainwin, &screenw, &screenh);
			SDL_GetMouseState(&mousex, &mousey);
			float nx = mousex;
			float ny = mousey;
			SDL_Point p = { mousex, mousey };
			convertToWorld(nx, ny, maincam);
			std::string exec = std::string("clickUpdates:Add(" + nx + "," + ny + ")");
			L->executeCode(exec);
			//    std::string execCod =
			//"tiles.reg['" + mp->tiles[x][y]->type->id + "']:onEnter(" + std::to_string(x) + ", " + std::to_string(y) +
		//	", " + std::to_string(lx) + ", " + std::to_string(ly) + ", " + std::to_string(dir) + ")";
		//std::cout << execCod << std::endl;
			L->executeCode(execCod);
			//std::cout << "It attempted to go here";
		}
    plr->handle(key, mp, L);
    maincam->camPos.x = plr->pos->x - 5;
    maincam->camPos.y = plr->pos->y - 5;
    renderToWorld(plr->pos, plr->w, plr->h, maincam, tex["player"]);
    std::string oss =
            std::string("") + std::to_string((int) (plr->pos->x + plr->w)) + ", " + std::to_string((int) plr->pos->y);
    text_curr = loadText(oss, col, 10, 10, 100, 100);
    SDL_DestroyTexture(text_curr);
    events->handle(L, mp);
}

void game::handle_game(camera *maincam, const Uint8 *key, map *mp) {
    int mousex, mousey;
    int screenw, screenh;
    SDL_GetWindowSize(mainwin, &screenw, &screenh);
    SDL_GetMouseState(&mousex, &mousey);
    int nx = mousex;
    int ny = mousey;
    //convertToWorld(nx, ny);
//	std::string oss = std::to_string(nx);
    std::string oss = std::string("") + std::to_string(mousex + (int) maincam->camPos.x) + ", " +
                      std::to_string((int) maincam->camPos.y + ny);
    text_curr = loadText(oss, col, nx + 30, ny + 20, 50, 20);
    SDL_DestroyTexture(text_curr);
    for (int i = 0; i < mp->pieces.size(); i++) {
        renderToWorld(mp->pieces[i]->pos, mp->pieces[i]->w, mp->pieces[i]->h, maincam, mp->pieces[i]->tex);
    }
    if (key[SDL_SCANCODE_D]) {
        maincam->camPos.x += 0.01 * ticks_per_frame;
    }
    if (key[SDL_SCANCODE_A]) {
        maincam->camPos.x -= 0.01 * ticks_per_frame;
    }
    if (key[SDL_SCANCODE_W]) {
        maincam->camPos.y += 0.01 * ticks_per_frame;
    }
    if (key[SDL_SCANCODE_S]) {
        maincam->camPos.y -= 0.01 * ticks_per_frame;
    }
    if (key[SDL_SCANCODE_N]) {
        maincam->w -= 0.01 * ticks_per_frame;
        maincam->h -= 0.01 * ticks_per_frame;
    }
    if (key[SDL_SCANCODE_M]) {
        maincam->w += 0.01 * ticks_per_frame;
        maincam->h += 0.01 * ticks_per_frame;
    }
}

game::game() {

}
