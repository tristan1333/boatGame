#include <cmath>
#include "vectors.h"
#include "SDL.h"

const float G_CONSTANT = 0.000000000067408f;

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
}

Vec2 Div(Vec2 Vec, float targNumb) {
    Vec.x = Vec.x / targNumb;
    Vec.y = Vec.y / targNumb;
    return Vec;
}

void Add(Vec2 *Vec, Vec2 ToAdd) {
    Vec->x += ToAdd.x;
    Vec->y += ToAdd.y;
    return;
}

Vec2 Sub(Vec2 Vec, Vec2 ToSub) {
    Vec.x -= ToSub.x;
    Vec.y -= ToSub.y;
    return Vec;
}

void Mult(Vec2 *Vec, float targNumb) {
    Vec->x = Vec->x * targNumb;
    Vec->y = Vec->y * targNumb;
    return;
}

float Mag(Vec2 Vec) {
    return std::sqrt(std::pow(Vec.x, 2) + std::pow(Vec.y, 2));
}

Vec2 Norm(Vec2 Vec) {
    return (Div(Vec, Mag(Vec)));
}

void Norm(Vec2 *Vec) {
    Vec2 Norm = (Div(*Vec, Mag(*Vec)));
    Vec->x = Norm.x;
    Vec->y = Norm.y;
    return;
}

float Dist(Vec2 Vec) {
    return Mag(Vec);
}

