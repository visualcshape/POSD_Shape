#include "Square.h"
#include <sstream>

using std::stringstream;

Square::Square(int ulx, int uly, int length)
	: Shape("square"), x(ulx), y(uly), length(length){
	generateBoundingBox();
}

string Square::print() {
	std::ostringstream oss;
	oss << name() << "(" << x << "," << y << "," << length << ")";

	return oss.str();
}

void Square::generateBoundingBox(){
	_boundingBox = BoundingBox(x, y, length, length);
}

int Square::area() const {
	return length * length;
}

string Square::describe() {
	stringstream ss;

	ss << "S(" << x << "," << y << "," << length << ")";

	return ss.str();
}

void Square::recalculateBoundingBox() {
	this->generateBoundingBox();
}

void Square::translation(QPoint translationLength) {
	int moveX = translationLength.x();
	int moveY = translationLength.y();
    this->x += moveX;
    this->y += moveY;
    this->generateBoundingBox();
}
