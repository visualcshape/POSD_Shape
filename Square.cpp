#include "Square.h"
#include <sstream>

Square::Square(int ulx, int uly, int length)
	:Shape("square"), _ulx(ulx), _uly(uly), _length(length){
	generateBoundingBox();
}

string Square::print() {
	std::ostringstream oss;
	oss << name() << "(" << _ulx << "," << _uly << "," << _length << ")";

	return oss.str();
}

void Square::generateBoundingBox(){
	_boundingBox = BoundingBox(_ulx, _uly, _length, _length);
}

int Square::area() const {
	return _length*_length;
}