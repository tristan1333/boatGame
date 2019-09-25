#include "camera.h"
#include "load_textures.h"
#include "resolutions.h"

#include <iostream>
int screen_Width = 640;
float worldToPixX = 32; //A unit is equal to 32 pixels.
float worldToPixY = 32; //Why 24 hol up
camera::camera(Vec2 pos, float w, float h, resHandler* res)
{
	this->camPos = pos;
	this->w = w;
	this->h = h;
	this->res = res;
}

void convertToWorld(float & x, float & y, camera* TargCam) //We simply want to take screen coordinates, and convert them to the world.
{
	//std::cout << TargCam->camPos.x;
	x = (x  /*(TargCam->camPos.x * TargCam->res->wldToScrx)*/) / TargCam->res->wldToScrx / (TargCam->res->w / (TargCam->w * TargCam->res->wldToScrx));
	x += (TargCam->camPos.x); //* (TargCam->res->w*(TargCam->w * TargCam->res->wldToScrx) / ));
	y = (y   / TargCam->res->wldToScry / (TargCam->res->h / (TargCam->h * TargCam->res->wldToScry)));
	y -= -(TargCam->camPos.y);
}
//(pos->x *  TargCam->res->wldToScrx) - (TargCam->camPos.x * TargCam->res->wldToScrx)) * (TargCam->res->w /(TargCam->w *  TargCam->res->wldToScrx))
//((pos->x *  TargCam->res->wldToScrx) - (TargCam->camPos.x * TargCam->res->wldToScrx)) * (TargCam->res->w / (TargCam->w *  TargCam->res->wldToScrx))
void renderToWorld(Vec2* pos, float w, float h, camera* TargCam, SDL_Texture * tex)
{

	float dw = w * worldToPixX  * (screen_Width/(TargCam->w * worldToPixX));
	renSpec(mainren, tex, w * TargCam->res->wldToScrx * (TargCam->res->w /(TargCam->w * TargCam->res->wldToScrx)) , h *  TargCam->res->wldToScry * (TargCam->res->h /(TargCam->h * TargCam->res->wldToScry)) , ((pos->x *  TargCam->res->wldToScrx) - (TargCam->camPos.x * TargCam->res->wldToScrx)) * (TargCam->res->w /(TargCam->w *  TargCam->res->wldToScrx)), ((pos->y *  TargCam->res->wldToScry ) - (TargCam->camPos.y * TargCam->res->wldToScry)) * (TargCam->res->h /(TargCam->h  * TargCam->res->wldToScry)));
} // W * worldToPix * (screen_width / camera Width * WorldToPix) gives a pixel accurate location to render to!!!																																																												((pos->x *  TargCam->res->wldToScrx) - (TargCam->camPos.x * TargCam->res->wldToScrx)) * (TargCam->res->w /(TargCam->w *  TargCam->res->wldToScrx)),																															
