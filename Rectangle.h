#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "shape.h"
#include "Point.h"

class Rectangle : public Shape {
private:
protected:
	void generateBoundingBox();
public:
	int length, width;
	Point positionPoint;

	Rectangle(Point p, int l, int w);
	Rectangle(int x, int y, int l, int w);
	string print();

    virtual void translation(QPoint translationLength);

	virtual QPoint getPosition();

	virtual void setPosition(QPoint position);

	int area() const;
	string describe();
	virtual void recalculateBoundingBox();
};

#endif