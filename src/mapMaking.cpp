#include "mapMaking.h"
#include "LuaContext.hpp"
#include <iostream>
#include "SDL.h"
#include "load_textures.h"
#include "camera.h"

#include <unordered_map>
#include "tileMap.h"
#include "tiles.h"

extern std::unordered_map<std::string, SDL_Texture *> tex;
extern std::vector<SDL_Texture *> textures;

tileInventory::tileInventory(LuaContext *L) {
    int numOreg = L->readVariable<int>("o_til_reg_n");
    std::cout << "Attemping to load tile inventory" << std::endl;
    for (int i = 1; i <= numOreg; i++) {
        std::string til = L->readVariable<std::string>("o_tile_reg", i, "id");
        this->tiles.push_back(til);
        std::cout << "Loaded " << til << " successfully" << std::endl;
        //std::cout << "Attemping to load " << L->readVariable<std::string>("o_tile_reg", i, "tex") << std::endl;
        //tex[L->readVariable<std::string>("o_tile_reg", i, "id")] = loadTexture(L->readVariable<std::string>("o_tile_reg", i, "tex"));
    }
    this->show = true;
    clickboxes.resize(11);
    for (int i = 0; i < clickboxes.size(); i++) {
        clickboxes[i] = new SDL_Rect();
        clickboxes[i]->w = 0;
        clickboxes[i]->h = 0;
    }
    this->curr_point = 0;
    this->curr_tile = "tile";
}

bool tileInventory::showInv() {
    return show;
}

void tileInventory::activate(int targ) {
    curr_tile = tiles[targ + curr_point];
    std::cout << curr_tile;
}

void tileInventory::checkClickCollison(SDL_Point p) {
    for (int i = 0; i < clickboxes.size(); i++) {
        if (clickboxes[i]->w == 0) {
            continue;
        }
        if (SDL_PointInRect(&p, clickboxes[i])) {
            activate(i);
            break;
        }
    }
}


void tileInventory::displayInventory() {
    renSpec(mainren, textures[1], 210, 130, 430, 350);
    renSpec(mainren, tex[curr_tile], 28, 28, 10, 430);
    for (int i = 0; i < this->tiles.size(); i++) {
        if (i <= 4) {
            renSpec(mainren, tex[tiles[i + curr_point]], 28, 28, 435 + (i * 32 + 20), 375);
            clickboxes[i]->x = 435 + (i * 32 + 20);
            clickboxes[i]->y = 375;
            clickboxes[i]->w = 28;
            clickboxes[i]->h = 28;
        } else if (i == curr_point + 9) {


            //curr_point = i;
            break;
        } else {
            clickboxes[i]->x = 435 + ((i - 5) * 32 + 20);
            clickboxes[i]->y = 415;
            clickboxes[i]->w = 28;
            clickboxes[i]->h = 28;
            renSpec(mainren, tex[tiles[i + curr_point]], 28, 28, 435 + ((i - 5) * 32 + 20), 415);
        }
    }
}

mapMakeHandler::mapMakeHandler(LuaContext *L) {
    //this->curr_tile = "tile";
    for (int i = 0; i != 6; i++) {
        this->saved_tiles[i] = "tile";
    }
    inventory = new tileInventory(L);
}

void mapMakeHandler::handle(camera *maincam, tilemap *mp) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_MOUSEMOTION) {

        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mousex, mousey;
            int screenw, screenh;
            //	SDL_GetWindowSize(mainwin, &screenw, &screenh);
            SDL_GetMouseState(&mousex, &mousey);
            float nx = mousex;
            float ny = mousey;
            SDL_Point p = {mousex, mousey};
            this->inventory->checkClickCollison(p);
            convertToWorld(nx, ny, maincam);
            //std::cout << "It attempted to go here";
            mp->tiles[(int) nx][(int) ny]->type->id = this->inventory->curr_tile;
        }
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_z) {
                savTileMap(mp);
            }
            if (e.key.keysym.sym == SDLK_ESCAPE) {
            }
        }
    }
    if (inventory->showInv()) {
        inventory->displayInventory();
    }
}