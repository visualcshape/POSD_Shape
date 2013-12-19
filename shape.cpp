#include "shape.h"
#include <vector>
#include <sstream>

using std::vector;

Circle::Circle(int cx, int cy, int radius)
	:_name("circle"), _cx(cx), _cy(cy), _radius(radius){}
string Circle::print() {
	std::ostringstream oss;
	oss << _name <<"("<<_cx<<","<<_cy<<","<<_radius<<")";
	return oss.str(); 
}

string Circle::name() {
	return _name;
}

Square::Square(int ulx, int uly, int length)
	:_name("square"),_ulx(ulx), _uly(uly), _length(length){}

string Square::name() {
	return _name;
}

string Square::print() {
	std::ostringstream oss;
	oss << _name <<"("<<_ulx<<","<<_uly<<","<<_length<<")";
	return oss.str(); 
}

string printShape(vector<void *> shapes){
	std::ostringstream oss;
	for (int i=0; i<shapes.size(); ++i )
		if (static_cast<Circle *>(shapes[i])->name()=="circle")
			oss <<  static_cast<Circle *>(shapes[i])->print() << "\n";
		else if (static_cast<Square *>(shapes[i])->name()=="square")
			oss <<  static_cast<Square *>(shapes[i])->print() << "\n";
	return oss.str();
} 
