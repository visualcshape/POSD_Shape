#include "cppunitlite\TestHarness.h"
#include "shape.h"

const double epsilon = 0.0000001;

int main(int argc, char** argv) {
	TestResult tr;
	TestRegistry::runAllTests(tr);

	return 0;
}

TEST (constructor, Circle) {
	Circle c(0,0,1);
	CHECK(string("circle")==c.print());
}

TEST (constructor, Square) {
	Square s(1,1,1);
	CHECK(string("square")==s.print());
}

