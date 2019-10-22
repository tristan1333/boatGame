#ifndef OBJ_H_
#define OBJ_H_
#include <string>
class gObj
{
public:
	double x;
	double y;
	double w;
	double h;
	std::string type;
	gObj(std::string, double, double, double, double);
};

#endif