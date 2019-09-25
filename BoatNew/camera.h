#ifndef CAMERA_H
#define CAMERA_H
#include "vectors.h"
#include "SDL.h"
class resHandler;
class camera
{
	public:
		camera(Vec2, float, float, resHandler*);
		Vec2 camPos;
		float w;
		float h;
		resHandler* res;
	private:
		
};
void renderToWorld(Vec2*, float, float, camera*, SDL_Texture*);
void convertToWorld(float&, float&, camera*);
void convertToRender(Vec2*, float, float);
#endif
