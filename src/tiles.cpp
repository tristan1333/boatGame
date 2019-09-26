#include "tileMap.h"
#include "tiles.h"
//#include "emptyTile.h"
#include "LuaContext.hpp"
#include "load_textures.h"
#include "vectors.h"

extern std::vector<SDL_Texture *> textures;

tile_type::tile_type(std::string tileid) {
    id = tileid;
}

tile::tile(Vec2 *pos, float w, float h) {
    this->type = new tile_type("tile");
    this->pos = new Vec2();
    this->pos->x = pos->x;
    this->pos->y = pos->y;
    this->w = w;
    this->h = h;
}

tile::tile() {
    this->type = new tile_type("tile");
    this->pos = new Vec2(0, 0);
}

tile::tile(std::string typ) {
    this->type = new tile_type(typ);
    this->pos = new Vec2(0, 0);
}
/*tilemap::tilemap(int w, int h)
{
	this->tiles.resize(w);
	for (int i = 0; i < h; ++i)
	{
    	tiles[i].resize(h);
	}
}*/
