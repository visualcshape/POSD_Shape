#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "shape.h"
#include "Point.h"

class Rectangle : public Shape {
private:
protected:
	void generateBoundingBox();
public:
	int height, width;
	Point positionPoint;

	Rectangle(Point p, int l, int w);
	Rectangle(int x, int y, int l, int w);
	string print();
	int area() const;
	string describe();
};

#endif