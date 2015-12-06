#ifndef _POINT_H_
#define _POINT_H_

#include "shape.h"

class Point : public Shape {
private:
	int _x, _y;
public:
	Point(int x, int y);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	string print();
};

#endif