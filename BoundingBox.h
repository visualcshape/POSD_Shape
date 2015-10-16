#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

class BoundingBox{
private:
	double _x;
	double _y;
	double _l;
	double _w;
public:
	BoundingBox(int x, int y, int l, int w) :_x(x), _y(y), _l(l), _w(w) {}

	inline double llx(){ return _x; }

	inline double lly(){ return _y; }

	inline double urx(){ return _x + _l; }

	inline double ury(){ return _y + _w; }

	inline double area(){ return _l*_w; }

	inline double l(){return _l;}

	inline double w(){return _w;}
};

#endif