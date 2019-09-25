
#include "SDL.h"
#include "fps_handler.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <ctime>
#include "map.h"
#include <iostream>
#include "load_textures.h"
#include "gameHandler.h"
#include "tiles.h"
#include "mainmenu.h"
#include "tilemap.h"
#include "luaFuncs.h"
#include "mapmaking.h"
#include "camera.h"
#include "LuaContext.hpp"
#include <fstream>
#include "resolutions.h"
#include "player.h"
#include "events.h"
#define MENU 1
#define GAME 2
#define MAP 3
extern std::vector<SDL_Texture*> textures;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//bool update_map = true; //What
int MENU_STATE = 0;
int MENUPICK = 0; //The state of a menu. Used with multiple menus.
int timer = 0; //Used for timing key presses. //Bleh
int GAME_STATE = MENU;
//SDL_Surface* mainsurface; //Pointer to the mainsurface. 
 //
//extern SDL_Renderer * mainren;
SDL_Texture * text;
extern TTF_Font * mainfont;
int main(int argc, char** argv) //The main function.
{
	srand(time(NULL));
	LuaContext lua;

	//lua.writeVariable("x", 5);
	//lua.executeCode("x = x + 2;");
//	lua.executeCode(std::istream{ "Scripts/Tiles/tile.lua" });
//lua.executeCode(std::ifstream{"script.lua"});
	//std::cout << lua.readVariable<int>("x") << std::endl;
	resHandler res = resHandler(640, 480, 1, 32, 32);
	if (!init(&res))
	{
		return 1;
	}
	if (!init_lua(&lua))
	{
		std::cout << "Lua failed!";
		return 1;
	}
	SDL_Event e;

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	int fps_time = SDL_GetTicks();
	double previous = SDL_GetTicks();
	double lag = 0.0;
	int frameps = 0;
	tilemap j = tilemap("MAP.vmf");

	camera maincam = camera(Vec2(0, 0), 10, 10, &res);
	game maingame = game();
	mapMakeHandler mpMkHandle = mapMakeHandler(&lua);
	init_player();
	player plr = player();
	mainMenu mainmen = mainMenu();
	eventHandler events = eventHandler();
	init_lua_map(&j, &lua);
	//std::cout << j.tiles[50][50]->type->id;
	bool quit = false;
	//	SDL_Rect john = {0,0,100,100};
	//	map mainmap = map(10);a
		//if(!loadMap(&mainmap))
		//{
		//	std::cout << "Failed load map";
		//	return 1;
		//}//
	//	platform pant(10,10,10,10, textures[0]);
		//SDL_RenderSetLogicalSize(mainren,SCREEN_WIDTH * res.resMod, SCREEN_HEIGHT * res.resMod);
	while (!quit)  																				//if(currentKeyStates[SDL_SCANCODE_UP]) function[SDL_DEFINED_KEYCODE]
	{
		//std::cout << "WENTHERE";
			//		double start = SDL_GetTicks();
			double current = SDL_GetTicks();
			double elapsed = current - previous;
			double targ = (ticks_per_frame * 100) / 10000;
			lag += elapsed;
			switch (GAME_STATE)
			{
			case MENU:
				SDL_RenderClear(mainren);
				GAME_STATE = mainmen.handle(&res);
				previous = SDL_GetTicks();
				break;
			case GAME:
				
				SDL_RenderClear(mainren);
				while (lag >= targ)
				{
					lag -= ticks_per_frame;
				}
			   maingame.handle_game(currentKeyStates, &maincam, &j, &plr, &lua, &events);
				break;
			//	maingame.handle_game(&maincam,currentKeyStates, &mainmap);
			case MAP:
				SDL_RenderClear(mainren);
				while (lag >= targ)
				{
					lag -= ticks_per_frame;
				}
				maingame.handle_game(currentKeyStates, &maincam, &j);
				mpMkHandle.handle(&maincam, &j);

			}
			SDL_RenderPresent(mainren);
			//	frameps++;
			SDL_PollEvent(&e);
			int capper = SDL_GetTicks() - get_Ticks();
			if (capper < ticks_per_frame)
			{
				SDL_Delay(ticks_per_frame - capper);
			}

			previous = current;
		}
	
}