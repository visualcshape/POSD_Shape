#ifndef _LINE_H_
#define _LINE_H_

#include "shape.h"

class Line : public Shape {
private:
	int _bx, _by;
	int _ex, _ey;
public:
	Line(int bx, int by, int ex, int ey);
	string print();
};

#endif