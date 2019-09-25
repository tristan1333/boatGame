#ifndef PLATFORMS_
#define PLATFORMS_
#include "SDL.h"
struct Vec2;
class platform
{
	public:
		platform(Vec2*, double, double, SDL_Texture*);
		platform();
		SDL_Texture *tex;
 		Vec2* pos;
 		double w;
 		double h;
};

#endif
