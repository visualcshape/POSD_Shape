#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Circle {
private:
	string _name;
	int _cx, _cy;
	int _radius;
public:
	Circle (int cx, int cy, int radius);
	string name();
	string print();
};

class Square {
private:
	string _name;
	int _ulx, _uly;
	int _length;
public:
	Square (int ulx, int uly, int length);
	string name();
	string print();
};

string printShape(vector<void *> shapes);
#endif
