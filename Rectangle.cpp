#include "Rectangle.h"
#include <sstream>

using std::stringstream;

Rectangle::Rectangle(Point p, int l, int w)
	:Shape("rectangle"), _ulc(p), _l(l), _w(w){}

Rectangle::Rectangle(int x, int y, int l, int w) : Shape("R"), _ulc(Point(x, y)), _l(l), _w(w){
	generateBoundingBox();
}

int Rectangle::area() const {
	return _l*_w;
}

string Rectangle::print() {
	std::ostringstream oss;
	oss << name() << "(point(" <<  _ulc.getX() << "," << _ulc.getY() << ")" << "," << _l << "," << _w << ")";
	return oss.str();
}

void Rectangle::generateBoundingBox(){
	_boundingBox = BoundingBox(_ulc.getX(), _ulc.getY(), _l, _w);
}

string Rectangle::describe() {
	stringstream ss;

	ss << "R(" << _ulc.getX() << "," << _ulc.getY() << "," << _l << "," << _w << ")";

	return ss.str();
}
