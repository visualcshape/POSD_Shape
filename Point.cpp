#include "Point.h"
#include <sstream>

Point::Point(int x, int y)
	:Shape("point"), _x(x), _y(y){}

int Point::getX(){
	return _x;
}

int Point::getY(){
	return _y;
}

string Point::print() {
	std::ostringstream oss;
	oss << name() << "(" << _x << "," << _y << ")";
	return oss.str();
}