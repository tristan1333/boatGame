#ifndef HITBOX_
#define HITBOX_

class hitbox {
public:
    double x;
    double y;
    double w;
    double h;

    hitbox();

    hitbox(double, double, double, double);
};

bool collide(hitbox, hitbox);

#endif
