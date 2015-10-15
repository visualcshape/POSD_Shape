#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "shape.h"

class Circle : public Shape {
private:
	int _cx, _cy;
	int _radius;

	void generateBoundingBox();
public:
	Circle(int cx, int cy, int radius);
	string print();
	virtual int area() const;
};

#endif