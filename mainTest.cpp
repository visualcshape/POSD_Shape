#include "cppunitlite/TestHarness.h"
#include "shape.h"
#include "Graphics.h"
#include "CompositeGraphics.h"
#include "SimpleGraphics.h"
#include <iostream>
#include <vector>
#include <typeinfo>
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Point.h"
#include "Line.h"
#include "AreaVisitor.h"
#include "DescriptionVisitor.h"

using std::vector;

const double epsilon = 0.0000001;

int main(int argc, char** argv) {
	TestResult tr;
	TestRegistry::runAllTests(tr);

	//system("pause");
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

TEST (ProblemStaticCast, Shape){
	Circle c(0,0,1);
	Square s(1,1,1);

	void *v = &s;
	Circle *pc = static_cast<Circle*>(v);
//	std::cout << pc->print();
	CHECK(string("square(1,1,1)")==pc->print());
	pc = reinterpret_cast<Circle *>(&s);
	CHECK(string("square(1,1,1)")==pc->print());

}

TEST (TotalArea, Shape) {
	Circle c(0,0,1);
	Square s(1,1,1);
	Point p(5,5);
	Line l(0,0,1,1);
	vector<Shape *>v;
	v.push_back(&c);
	v.push_back(&s);
	v.push_back(&l);
	v.push_back(&p);

	LONGS_EQUAL(4, totalArea(v));
}

TEST (Rectangle, Shape){
	Rectangle r(Point(1,1),2,3);
	CHECK(string("rectangle(point(1,1),2,3)")==r.print());
	LONGS_EQUAL(6,r.area());
}

TEST(areaSum, Rectangle) {
	Rectangle r1(0, 0, 1, 2), r2(0, 0, 2, 3), r3(0, 0, 3, 4);
	std::vector<Shape *> v;
	v.push_back(&r1);
	v.push_back(&r2);
	v.push_back(&r3);
	LONGS_EQUAL(20, areaSum(v));
}

TEST(areaSum, allShapes) {
	Circle c(0, 0, 1);
	Square s(0, 0, 2);
	Rectangle r(0, 0, 3, 4);
	std::vector<Shape *> v;
	v.push_back(&c);
	v.push_back(&s);
	v.push_back(&r);
	LONGS_EQUAL(19, areaSum(v));
}

TEST(Shape, getBoundingBox) {
	Circle c(0, 0, 1);
	Rectangle r(1, 1, 1, 2);
	Square s(0, 0, 3);

	// bounding box of a shape is a rectangle
	LONGS_EQUAL(-1, c.getBoundingBox().llx());
	LONGS_EQUAL(-1, c.getBoundingBox().lly());
	LONGS_EQUAL(1, c.getBoundingBox().urx());
	LONGS_EQUAL(1, c.getBoundingBox().ury());

	LONGS_EQUAL(1, r.getBoundingBox().llx());
	LONGS_EQUAL(1, r.getBoundingBox().lly());
	LONGS_EQUAL(2, r.getBoundingBox().urx());
	LONGS_EQUAL(3, r.getBoundingBox().ury());

	LONGS_EQUAL(0, s.getBoundingBox().llx());
	LONGS_EQUAL(0, s.getBoundingBox().lly());
	LONGS_EQUAL(3, s.getBoundingBox().urx());
	LONGS_EQUAL(3, s.getBoundingBox().ury());

	LONGS_EQUAL(4, c.getBoundingBox().area());
	LONGS_EQUAL(2, r.getBoundingBox().area());
	LONGS_EQUAL(9, s.getBoundingBox().area());
}

TEST(Graphics, defaultBoundingBox) {
	Graphics g;
	// Graphics object has a default bounding box of
	// rectangle (0,0,0,0)
	LONGS_EQUAL(0, g.getBoundingBox().llx());
	LONGS_EQUAL(0, g.getBoundingBox().lly());
	LONGS_EQUAL(0, g.getBoundingBox().urx());
	LONGS_EQUAL(0, g.getBoundingBox().ury());
}

TEST(CompositeGraphics, defaultBoundingBox) {
	CompositeGraphics g;
	// CompositeGraphics object has a default bounding box of
	// rectangle (0,0,0,0)
	LONGS_EQUAL(0, g.getBoundingBox().llx());
	LONGS_EQUAL(0, g.getBoundingBox().lly());
	LONGS_EQUAL(0, g.getBoundingBox().urx());
	LONGS_EQUAL(0, g.getBoundingBox().ury());
	LONGS_EQUAL(0, g.getBoundingBox().area());
}

TEST(SimpleGraphics, ctor_BoundingBox) {
	// SimpleGraphics object points to a Shape object
	Graphics *g1 = new SimpleGraphics(new Circle(0, 0, 1));
	Graphics *g2 = new SimpleGraphics(new Square(0, 0, 2));
	Graphics *g3 = new SimpleGraphics(new Rectangle(5, 6, 3, 4));

	LONGS_EQUAL(-1, g1->getBoundingBox().llx());
	LONGS_EQUAL(-1, g1->getBoundingBox().lly());
	LONGS_EQUAL(1, g1->getBoundingBox().urx());
	LONGS_EQUAL(1, g1->getBoundingBox().ury());

	LONGS_EQUAL(0, g2->getBoundingBox().llx());
	LONGS_EQUAL(0, g2->getBoundingBox().lly());
	LONGS_EQUAL(2, g2->getBoundingBox().urx());
	LONGS_EQUAL(2, g2->getBoundingBox().ury());

	LONGS_EQUAL(5, g3->getBoundingBox().llx());
	LONGS_EQUAL(6, g3->getBoundingBox().lly());
	LONGS_EQUAL(8, g3->getBoundingBox().urx());
	LONGS_EQUAL(10, g3->getBoundingBox().ury());

}

TEST(SimpleGraphics, AddingGraphicsObjectShouldThrowException) {
	SimpleGraphics g(new Circle(0, 0, 1));
	// adding Graphics throws an exception
	try {
		g.add(new Graphics);
	}
	catch (std::string s) {
		CHECK(std::string("Cannot add child") == s);
	}
	// adding SimpleGraphics throws an exception
	try {
		g.add(new SimpleGraphics(new Circle(0, 0, 1)));
	}
	catch (std::string s) {
		CHECK(std::string("Cannot add child") == s);
	}

	// adding CompositeGraphics throws an exception
	try {
		g.add(new CompositeGraphics);
	}
	catch (std::string s) {
		CHECK(std::string("Cannot add child") == s);
	}
}

TEST(CompositeGraphics, addingOneChild) {
	CompositeGraphics g;

	try {
		g.add(new SimpleGraphics(new Circle(0, 0, 2)));
	}
	catch (std::string s) {
		FAIL("Should not throw exception");
	}

	LONGS_EQUAL(16, g.getBoundingBox().area());
}

TEST(CompositeGraphics, addingTwoChildrenAndGetBoundingBox) {
	CompositeGraphics g;

	g.add(new SimpleGraphics(new Circle(0, 0, 1)));
	g.add(new SimpleGraphics(new Square(-2, -2, 2)));

	LONGS_EQUAL(-2, g.getBoundingBox().llx());
	LONGS_EQUAL(-2, g.getBoundingBox().lly());
	LONGS_EQUAL(1, g.getBoundingBox().urx());
	LONGS_EQUAL(1, g.getBoundingBox().ury());
}

TEST(CompositeGraphics, SimpleAndCompositeChildrenAndGetBoundingBox) {
	CompositeGraphics g;
	SimpleGraphics r(new Rectangle(-1, -1, 1, 3));

	g.add(new SimpleGraphics(new Circle(0, 0, 1)));
	g.add(new SimpleGraphics(new Square(-2, -2, 2)));
	CompositeGraphics h;
	h.add(&g);
	h.add(&r);

	LONGS_EQUAL(-2, h.getBoundingBox().llx());
	LONGS_EQUAL(-2, h.getBoundingBox().lly());
	LONGS_EQUAL(1, h.getBoundingBox().urx());
	LONGS_EQUAL(2, h.getBoundingBox().ury());
}

TEST(AreaVisitor, derivedFromGaphicsVisitor) {
	CompositeGraphics g;
	g.add(new SimpleGraphics(new Circle(0,0,1)));
	g.add(new SimpleGraphics(new Square(-2,-2,2)));
	SimpleGraphics r(new Rectangle (-1,-1,1,3));
	CompositeGraphics h;

	h.add(&g);
	h.add(&r);

	GraphicsVisitor * av = new AreaVisitor();
	h.accept(*av);

	LONGS_EQUAL(10, static_cast<AreaVisitor *>(av)->area());
}

TEST (Shape, descriptions) {
    Shape * c = new Circle(0,0,1);
    CHECK(std::string("C(0,0,1)")== c->describe());
    c = new Square(0,0,1);
    CHECK(std::string("S(0,0,1)")== c->describe());
    c = new Rectangle(0,0,1,2);
    CHECK(std::string("R(0,0,1,2)")== c->describe());
}


TEST (DescVisitor, SimpleGraphics) {
	SimpleGraphics s(new Rectangle(0,0,2,3));
	DescriptionVisitor dv;
	s.accept(dv);

	CHECK(std::string("R(0,0,2,3)\n")==dv.getDescription());
}

TEST (DescVisitor, CompositeGraphics) {
    CompositeGraphics g;
    g.add(new SimpleGraphics(new Circle(0,0,1)));
    g.add(new SimpleGraphics(new Square(-2,-2,2)));

    DescriptionVisitor dv;
    g.accept(dv);

    std::string ans("Comp R(-2,-2,3,3)\n");
    ans += std::string("  C(0,0,1)\n");
    ans += std::string("  S(-2,-2,2)\n");
    std::cout << dv.getDescription() << std::endl;
    CHECK(ans==dv.getDescription());
}

TEST (DescVisitor, CompositeGraphicsWithComposite) {
    CompositeGraphics g;
    g.add(new SimpleGraphics(new Circle(0,0,1)));
    g.add(new SimpleGraphics(new Square(-2,-2,2)));

    SimpleGraphics r(new Rectangle (-1,-1,1,3));

    CompositeGraphics h;
    h.add(&g);
    h.add(&r);

    DescriptionVisitor dv;
    h.accept(dv);

    std::string ans("Comp R(-2,-2,3,4)\n");
    ans += std::string("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    std::cout << dv.getDescription() << std::endl;
    CHECK(ans==dv.getDescription());
}