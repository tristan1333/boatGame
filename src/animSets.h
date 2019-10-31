#ifndef ANIMSETS_H_
#define ANIMSETS_H_
#include <vector>
#include "SDL.h"
#include "timers.h"
class animLoop
{
	public:
		std::vector<SDL_Texture*> textures;
		int activeTex;
		timer* loop;
		void checkLoop();
		void handleChange();
		animLoop(std::vector<SDL_Texture*>, int);
		animLoop(SDL_Texture*, int);
};
#endif