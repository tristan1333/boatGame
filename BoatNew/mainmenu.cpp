#include "mainmenu.h"
#include <string>
#include "SDL.h"
#include "load_textures.h"
#include "resolutions.h"
mainMenu::mainMenu()
{

}

int mainMenu::handle(resHandler * res)
{
	int tx_wd = res->w / 4 * res->resMod;
	int tx_h = res->h / 4 * res->resMod;
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			int mousex, mousey = 0;
			SDL_GetMouseState(&mousex, &mousey);
			SDL_Point p = { mousex, mousey };
			SDL_Rect play = { res->w / 10 * res->resMod , res->h / 8 * res->resMod , tx_wd, tx_h };
			SDL_Rect map = { res->w / 10 * res->resMod, res->h / 8 * res->resMod + tx_h + (tx_h / 2), tx_wd, tx_h };
			if (SDL_PointInRect(&p, &play))
			{
				return 2;
			}
			if (SDL_PointInRect(&p, &map))
			{
				return 3;
			}
			//std::cout << "It attempted to go here";
		}
	}
	SDL_Color col{ 200,100,4,255 };

	SDL_Texture* text_curr = loadText("Play Game", col, res->w/10 * res->resMod, res->h / 8 * res->resMod, tx_wd, tx_h );
	SDL_DestroyTexture(text_curr);
	text_curr = loadText("Edit Map", col, res->w / 10 * res->resMod, res->h / 8 * res->resMod + tx_h + (tx_h/2), tx_wd, tx_h);
	SDL_DestroyTexture(text_curr);
	return 1;
}