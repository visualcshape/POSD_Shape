#include "shape.h"

Circle::Circle(int cx, int cy, int radius)
	:_name("circle"), _cx(cx), _cy(cy), _radius(radius){}
string Circle::print() {
	return _name;
}

Square::Square(int ulx, int uly, int length)
	:_name("square"),_ulx(ulx), _uly(uly), _length(length){}
string Square::print() {
	return _name;
}

void printShape(vector<?> shapes){
	for (int i=0; i<shapes.size(); ++i)
		cout << shapes[i].print() << "\n";
} 
