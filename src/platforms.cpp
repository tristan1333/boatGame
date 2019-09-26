#include "platform.h"
#include "SDL.h"
#include "vectors.h"
#include <vector>

extern std::vector<SDL_Texture *> textures;

platform::platform(Vec2 *vec, double w, double h, SDL_Texture *tex) {
    this->pos = vec;
    this->w = w;
    this->h = h;
    this->tex = tex;
}

platform::platform() {
    this->pos = new Vec2(1, 1);
    this->w = 1;
    this->h = 1;
    this->tex = textures[0];
}
