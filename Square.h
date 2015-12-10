#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "shape.h"

class Square : public Shape{
private:

	void generateBoundingBox();
public:
	int x, y;
	int length;
	Square(int ulx, int uly, int length);
	string print();
	virtual int area() const;
    string describe();
	virtual void recalculateBoundingBox();

    virtual void translation(QPoint translationLength);

	virtual QPoint getPosition();

	virtual void setPosition(QPoint position);
};

#endif