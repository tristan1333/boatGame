#include "luaFuncs.h"
#include "tiles.h"
#include <fstream>

#define IGNORE_FIRST -1
#define GET_TILES 0
#define GET_PLAYER 1
#define GET_MAP 2

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include "LuaContext.hpp"
#include "load_textures.h"

std::unordered_map<std::string, SDL_Texture *> tex;

void load_lua_textures(LuaContext *L) {
    int numOreg = L->readVariable<int>("o_til_reg_n");
    for (int i = 1; i <= numOreg; i++) {
        //std::cout << "haha";
        std::cout << "Attemping to load " << L->readVariable<std::string>("o_tile_reg", i, "tex") << std::endl;
        tex[L->readVariable<std::string>("o_tile_reg", i, "id")] = loadTexture(
                L->readVariable<std::string>("o_tile_reg", i, "tex"));
    }
    //std::cout << L->readVariable<std::string>("o_tile_reg", 1, "id");

    //std::cout << lua.readVariable<int>("x") << std::endl;
}

void load_lua_files(std::string &tileFile, LuaContext *L) {
    std::ifstream file;
    file.open("Scripts/loadLua.blf");
    std::string line;
    int state = IGNORE_FIRST;
    while (getline(file, line)) {
        //std::cout << line;
        if (state == IGNORE_FIRST) {
            state = GET_TILES;
            continue;
        } else if (state == GET_TILES) {

            //tileFile = line;
            std::ifstream luFile;
            luFile.open(line);
            std::string luLine;
            getline(luFile, luLine);
            while (getline(luFile, luLine)) {
                std::cout << "Attemping to load " << luLine << std::endl;
                std::ifstream loadLuaFile;
                loadLuaFile.open(luLine);
                L->executeCode(loadLuaFile);
                loadLuaFile.close();
                std::cout << "Succeeded to load " << luLine << std::endl;
                continue;
            }
            luFile.close();
            state = GET_PLAYER;
            continue;
        } else if (state == GET_PLAYER) {
            std::ifstream luFile;
            luFile.open(line);
            std::string luLine;
            getline(luFile, luLine);
            while (getline(luFile, luLine)) {
                std::cout << "Attempting to load " << luLine << std::endl;
                std::ifstream loadLuaFile;
                loadLuaFile.open(luLine);
                L->executeCode(loadLuaFile);
                loadLuaFile.close();
                std::cout << "Succeeded to load " << luLine << std::endl;
                continue;
            }
        } else if (state == GET_MAP) {
            std::ifstream luFile;
            luFile.open(line);
            std::string luLine;
            getline(luFile, luLine);
            while (getline(luFile, luLine)) {
                std::cout << "Attempting to load " << luLine << std::endl;
                std::ifstream loadLuaFile;
                loadLuaFile.open(luLine);
                L->executeCode(loadLuaFile);
                loadLuaFile.close();
                std::cout << "Succeeded to load " << luLine << std::endl;
                continue;
            }
        } else {
            file.close();
            return;
        }
    }

}

void load_tiles(std::string tileFile) {
    std::ifstream file;
    file.open(tileFile);
    std::string line;
    int state = IGNORE_FIRST;
    while (getline(file, line)) {
        if (state == IGNORE_FIRST) {
            continue;
        } else {

        }
    }
}

bool init_lua(LuaContext *L) {
    std::string tileFile = std::string("");
//	L->registerFunction("tile_type", &tile_type::create);
    std::ifstream file;
    file.open("Scripts/Tiles/tile.lua");
    L->executeCode(file);
    file.close();
    //std::cout << L->readVariable<std::string>("tile", "id");
    load_lua_files(tileFile, L);
    load_lua_textures(L);
    std::cout << "Finished loading tiles!" << std::endl;
    //std::count << L->readVariable<std::string>()
//	std::cout << "Bruh";
    //L->executeCode("emptyTile:change()");
    //load_tiles(tileFile);
    return true;
}

//YOU HAVE LUA FILE LOADING, YOU NEED TO LOAD THE TILES, CURRENTLY, CREATING FUNCTIONS FOR LUA TO ACCESS FROM TILES!!!
//
//