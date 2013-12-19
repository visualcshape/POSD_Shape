#ifndef SHAPE_H
#define SHAPE_H

#include <string>

using std::string;

class Circle {
private:
	string _name;
	int _cx, _cy;
	int _radius;
public:
	Circle (int cx, int cy, int radius);
	string print();
};

class Square {
private:
	string _name;
	int _ulx, _uly;
	int _length;
public:
	Square (int ulx, int uly, int length);
	string print();
};

#endif
