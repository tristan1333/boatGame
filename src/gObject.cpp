#include "objects.h"
#include <string>
gObj::gObj(std::string ID, double x, double y, double w, double h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->type = ID;
}