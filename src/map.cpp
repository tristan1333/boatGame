#include "load_textures.h"
#include "platform.h"
#include "map.h"
#include "vectors.h"
#include <fstream>
#include <string>
#include <iostream>

#define LOOKING_FOR_START 0
#define LOOKING_FOR_FILES 1
#define LOAD_MAP 2
#define FINISH_LOAD 3
#define FINDX 0
#define FINDY 1
#define FINDW 2
#define FINDH 3
#define FINDTEX 4
extern std::vector<SDL_Texture *> textures;

map::map(int size) {
//	this->pieces.resize(size);
}

double numbify(std::string str) {
    return std::stod(str.c_str());
}

int numbifyint(std::string str) {
    return strtol(str.c_str(), 0, 10);
}

bool loadMap(map *mp) {
    //set_pieces.clear();
    std::ifstream file;
    file.open("MAP.vmf");
    std::string line;
    int mp_state = 0;
    double x;
    double y;
    double w;
    double h;
    int tex_ref;
    int type_ref;
    int state = 0;
    int priority = 0;
    int preSize = textures.size();
    while (getline(file, line)) {
        std::cout << line;
        if (state == LOOKING_FOR_START) {
            if (line != "START") {

                return false;
            }
            state = LOOKING_FOR_FILES;
            continue;
        }
        if (state == LOOKING_FOR_FILES) {
            if (line == "ENDTEX") {
                state = LOAD_MAP;
                continue;
            }
            textures.push_back(loadTexture(line));
            continue;
        }
        if (state == LOAD_MAP) {
            if (line == "END") {
                state = FINISH_LOAD;
                return true;
                continue;
            }
            switch (mp_state) {
                case FINDX:
                    x = numbify(line);
                    mp_state++;
                    break;
                case FINDY:
                    y = numbify(line);
                    mp_state++;
                    break;
                case FINDW:
                    w = numbify(line);
                    mp_state++;
                    break;
                case FINDH:
                    h = numbify(line);
                    mp_state++;
                    break;
                case FINDTEX:
                    tex_ref = numbifyint(line);
                    mp->pieces.push_back(new platform(new Vec2(x, y), w, h, textures[tex_ref + preSize]));
                    mp_state = FINDX;
                    break;

            }
            continue;
        }
        if (state == FINISH_LOAD) {
            return true;
        }
    }
}
