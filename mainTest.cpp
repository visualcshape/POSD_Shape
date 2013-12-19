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
	vector<void *>v;
	void *p = &c;
	v.push_back(&c);
	v.push_back(&s);	
	CHECK(string("circle(0,0,1)")==static_cast<Circle*>(v[0])->print());
	CHECK(string("square(1,1,1)")==static_cast<Square*>(v[1])->print());
	
	CHECK(string("circle(0,0,1)\nsquare(1,1,1)\n")==printShape(v));
}
