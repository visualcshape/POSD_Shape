#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "shape.h"

class Square : public Shape{
private:
	int _ulx, _uly;
	int _length;

	void generateBoundingBox();
public:
	Square(int ulx, int uly, int length);
	string print();
	virtual int area() const;
    string describe();
};

#endif