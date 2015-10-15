#include "Circle.h"
#include <sstream>

Circle::Circle(int cx, int cy, int radius)
	:Shape("circle"), _cx(cx), _cy(cy), _radius(radius){
	generateBoundingBox();
}

string Circle::print() {
	std::ostringstream oss;
	oss << name() << "(" << _cx << "," << _cy << "," << _radius << ")";
	return oss.str();
}

void Circle::generateBoundingBox(){
	_boundingBox = BoundingBox(_cx - _radius, _cy - _radius, 2 * _radius, 2 * _radius);
}

int Circle::area() const {
	return 3 * _radius*_radius;
}