#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "shape.h"

class Circle : public Shape {
private:
	void generateBoundingBox();
public:
	int centerX, centerY;
	int radius;
	Circle(int cx, int cy, int radius);
	string print();
	virtual int area() const;
	string describe();
};

#endif