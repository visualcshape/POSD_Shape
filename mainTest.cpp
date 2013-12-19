#include "cppunitlite\TestHarness.h"
#include "shape.h"
#include <iostream>
#include <vector>
#include <typeinfo>

using std::vector;

const double epsilon = 0.0000001;

int main(int argc, char** argv) {
	TestResult tr;
	TestRegistry::runAllTests(tr);

	return 0;
}

TEST (constructor, Circle) {
	Circle c(0,0,1);
	CHECK(string("circle(0,0,1)")==c.print());
}

TEST (constructor, Square) {
	Square s(1,1,1);
	CHECK(string("square(1,1,1)")==s.print());
}

TEST (print, Shape){
	Circle c(0,0,1);
	Square s(1,1,1);
	vector<Shape *>v;
	v.push_back(&c);
	v.push_back(&s);	
	CHECK(string("circle(0,0,1)")==v[0]->print());
	CHECK(string("square(1,1,1)")==v[1]->print());
	CHECK(string("circle(0,0,1)\nsquare(1,1,1)\n")==printShape(v));
}

TEST (Line, Shape){
	Line l(0,0,1,1);
	Circle c(0,0,1);
	Square s(1,1,1);

	vector<Shape *>v;
	v.push_back(&c);
	v.push_back(&s);	
	v.push_back(&l);	

	CHECK(string("line(0,0,1,1)")==v[2]->print());
	CHECK(string("circle(0,0,1)\nsquare(1,1,1)\nline(0,0,1,1)\n")==printShape(v));
}

TEST (Point, Shape){
	Point p(5,5);
	Line l(0,0,1,1);
	Circle c(0,0,1);
	Square s(1,1,1);

	vector<Shape *>v;
	v.push_back(&c);
	v.push_back(&s);	
	v.push_back(&l);
	v.push_back(&p);	

	CHECK(string("point(5,5)")==v[3]->print());
	CHECK(string("circle(0,0,1)\nsquare(1,1,1)\nline(0,0,1,1)\npoint(5,5)\n")==printShape(v));
}
