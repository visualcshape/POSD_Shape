#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
#include <iostream>

#include "BoundingBox.h"
#include <QPoint>

using std::string;
using std::vector;
using std::ostream;

class Shape{
private:
	string _name;
protected:
	BoundingBox _boundingBox;

	//A pure virtual function generates the bounding box
	virtual void generateBoundingBox(){}
public:
	Shape(string name);
	string name();
	virtual string print();
	virtual int area() const;
	inline virtual BoundingBox getBoundingBox(){ return _boundingBox; }
    virtual string describe(){};
	virtual void recalculateBoundingBox(){}
	virtual void translation(QPoint translationLength){}
};

//Global Function
string printShape(vector<Shape *> shapes);

int totalArea(vector<Shape *> shapes);

ostream & operator << (ostream &, Shape & s);

double areaSum(std::vector<Shape*> shapes);

#endif
