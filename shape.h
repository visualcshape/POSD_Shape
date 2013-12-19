#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Shape {
private:
	string _name;
public:
	Shape (string name);
	string name();
	virtual string print();
};

class Circle : public Shape {
private:
	int _cx, _cy;
	int _radius;
public:
	Circle (int cx, int cy, int radius);
	string print();
};

class Square : public Shape{
private:
	int _ulx, _uly;
	int _length;
public:
	Square (int ulx, int uly, int length);
	string print();
};

class Line : public Shape {
private:
	int _bx, _by;
	int _ex, _ey;
public:
	Line (int bx, int by, int ex, int ey);
	string print();
};

string printShape(vector<Shape *> shapes);
#endif
