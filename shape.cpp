#include "shape.h"
#include <vector>
#include <sstream>

using std::vector;

Shape::Shape(string name)
	:_name(name), _boundingBox(0, 0, 0, 0){}

string Shape::name() {
	return _name;
}

string Shape::print() {
	return name();
}

int Shape::area() const {
	return 0;
}

//Global Functions
string printShape(vector<Shape *> shapes){
	std::ostringstream oss;
	for (int i = 0; i < shapes.size(); ++i)
		oss << shapes[i]->print() << "\n";
	return oss.str();
}

int totalArea(vector<Shape *> shapes){
	int area = 0;
	for (int i = 0; i < shapes.size(); ++i)
		area += shapes[i]->area();
	return area;
}

double areaSum(vector<Shape*> shapes){
	double returnArea = 0;

	for (vector<Shape*>::iterator iterator = shapes.begin(); iterator != shapes.end(); iterator++)
		returnArea += (*iterator)->area();

	return returnArea;
}

ostream & operator << (ostream & os, Shape & s) {
	return os << s.print();
}

