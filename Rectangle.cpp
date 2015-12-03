#include "Rectangle.h"
#include <sstream>

using std::stringstream;

Rectangle::Rectangle(Point p, int l, int w)
	: Shape("rectangle"), positionPoint(p), height(l), width(w){}

Rectangle::Rectangle(int x, int y, int l, int w) : Shape("R"), positionPoint(Point(x, y)), height(l), width(w){
	generateBoundingBox();
}

int Rectangle::area() const {
	return height * width;
}

string Rectangle::print() {
	std::ostringstream oss;
	oss << name() << "(point(" << positionPoint.getX() << "," << positionPoint.getY() << ")" << "," << height << "," << width << ")";
	return oss.str();
}

void Rectangle::generateBoundingBox(){
	_boundingBox = BoundingBox(positionPoint.getX(), positionPoint.getY(), height, width);
}

string Rectangle::describe() {
	stringstream ss;

	ss << "R(" << positionPoint.getX() << "," << positionPoint.getY() << "," << height << "," << width << ")";

	return ss.str();
}
