#ifndef TILEs_
#define TILEs_
#include <vector>
#include <string>
#include "SDL.h"
class Vec2;
class LuaContext;
class tile_type
{
		public:
			//SDL_Texture* tex;
			tile_type(std::string);
			std::string id;
};



class tile
{
	public:
		tile_type* type;
		Vec2* pos;
		float w;
		float h;
		tile(Vec2*, float, float);
		tile();
		tile(std::string);
};


#endif

/*#ifndef TILEs_
#define TILEs_
#include "SDL.h"
#include <vector>
class Vec2;
extern std::vector<SDL_Texture*> textures;
class tile_type
{
		public:
			SDL_Texture* tex;
};

class empty_tile : public tile_type
{
	public:
		empty_tile();
};

class tile
{
	public:
		tile_type* type;
		Vec2* pos;
		float w;
		float h;
		tile(Vec2*, float, float);
		tile();
};

class tilemap
{
	public:
		std::vector<std::vector<tile> > tiles;
		tilemap(int, int);
};

#endif*/
