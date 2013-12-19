#include "shape.h"
#include <vector>
#include <sstream>

using std::vector;

Shape::Shape(string name)
	:_name(name){}

string Shape::name() {
	return _name;
}

string Shape::print() {
	return name();
}
Circle::Circle(int cx, int cy, int radius)
	:Shape("circle"), _cx(cx), _cy(cy), _radius(radius){}
	
string Circle::print() {
	std::ostringstream oss;
	oss << name() <<"("<<_cx<<","<<_cy<<","<<_radius<<")";
	return oss.str(); 
}

Square::Square(int ulx, int uly, int length)
	:Shape("square"),_ulx(ulx), _uly(uly), _length(length){}

string Square::print() {
	std::ostringstream oss;
	oss << name() <<"("<<_ulx<<","<<_uly<<","<<_length<<")";
	return oss.str(); 
}

string printShape(vector<Shape *> shapes){
	std::ostringstream oss;
	for (int i=0; i<shapes.size(); ++i )
		oss <<  shapes[i]->print() << "\n";
	return oss.str();
} 

Line::Line(int bx, int by, int ex, int ey)
	:Shape("line"),_bx(bx),_by(by),_ex(ex),_ey(ey){}

string Line::print() {
	std::ostringstream oss;
	oss << name() <<"("<<_bx<<","<<_by<<","<<_ex<<","<<_ey<<")";
	return oss.str(); 
}

