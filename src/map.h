#ifndef MAPS_H
#define MAPS_H

#include <vector>

class platform;

class map {
public:
    std::vector<platform *> pieces;

    map(int);
};

bool loadMap(map *);

#endif
