#ifndef VectorMath

class Vec2 {
public:
    float x;
    float y;

    Vec2(float, float);

    Vec2();
};

Vec2 Div(Vec2 Vec, float targNumb);

void Add(Vec2 *, Vec2);

Vec2 Sub(Vec2, Vec2);

void Mult(Vec2 *, float targNumb);

float Mag(Vec2);

Vec2 Norm(Vec2);

void Norm(Vec2 *);

float Dist(Vec2);

#endif
