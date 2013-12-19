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
		else if (static_cast<Line *>(shapes[i])->name()=="line")
			oss <<  static_cast<Line *>(shapes[i])->print() << "\n";
	return oss.str();
} 

Line::Line(int bx, int by, int ex, int ey)
	:_name("line"),_bx(bx),_by(by),_ex(ex),_ey(ey){}

string Line::name() {
	return _name;
}

string Line::print() {
	std::ostringstream oss;
	oss << _name <<"("<<_bx<<","<<_by<<","<<_ex<<","<<_ey<<")";
	return oss.str(); 
}

