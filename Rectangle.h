#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "shape.h"
#include "Point.h"

class Rectangle : public Shape {
private:
protected:
	Point _ulc;
	int _l, _w;

	void generateBoundingBox();
public:
	Rectangle(Point p, int l, int w);
	Rectangle(int x, int y, int l, int w);
	string print();
	int area() const;
};

#endif