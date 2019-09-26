#include "renderWrld.h"
#include "load_textures.h"
#include "camera.h"

double aspectMod = 1;
float worldToPix = 32; //A unit is equal to 32 pixels.
extern std::unordered_map<std::string, SDL_Texture *> tex;
//void renderToWorld(Vec2* pos, float w, float h, camera TargCam, SDL_Texture * text)
//{
//	float screen_Width = 480;
//	float screen_height = 640;
//	renSpec(mainren, text, w * worldToPix  * (screen_Width/(TargCam.w * worldToPix)), h * worldToPix * (screen_height/(TargCam.h * worldToPix)), (pos->x * worldToPix) - (TargCam.camPos.x * worldToPix), (pos->y * worldToPix) + (TargCam.camPos.y * worldToPix));
//} // W * worldToPix * (screen_width / camera Width * WorldToPix) gives a pixel accurate location to render to!!!
