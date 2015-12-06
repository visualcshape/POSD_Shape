#include "Rectangle.h"
#include <sstream>

using std::stringstream;

Rectangle::Rectangle(Point p, int l, int w)
	: Shape("rectangle"), positionPoint(p), length(l), width(w){}

Rectangle::Rectangle(int x, int y, int l, int w) : Shape("R"), positionPoint(Point(x, y)), length(l), width(w){
	generateBoundingBox();
}

int Rectangle::area() const {
	return length * width;
}

string Rectangle::print() {
	std::ostringstream oss;
	oss << name() << "(point(" << positionPoint.getX() << "," << positionPoint.getY() << ")" << "," << length << "," << width << ")";
	return oss.str();
}

void Rectangle::generateBoundingBox(){
	_boundingBox = BoundingBox(positionPoint.getX(), positionPoint.getY(), length, width);
}

string Rectangle::describe() {
	stringstream ss;

	ss << "R(" << positionPoint.getX() << "," << positionPoint.getY() << "," << length << "," << width << ")";

	return ss.str();
}

void Rectangle::recalculateBoundingBox() {
    this->generateBoundingBox();
}

void Rectangle::translation(QPoint translationLength) {
    this->positionPoint.setX(this->positionPoint.getX()+translationLength.x());
    this->positionPoint.setY(this->positionPoint.getY()+translationLength.y());
    this->generateBoundingBox();
}
