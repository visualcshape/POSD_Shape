#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_
#include <string>
#include "BoundingBox.h"
#include "GraphicsVisitor.h"

class Graphics{
protected:
	BoundingBox _boundingBox;
public:
	Graphics():_boundingBox(0,0,0,0){}

	virtual BoundingBox getBoundingBox(){ return _boundingBox; }
	
	virtual void add(Graphics* graphic){ throw std::string("Cannot add child"); }

	virtual void accept(GraphicsVisitor &graphicVisitor) {};

	virtual double calculateArea(){return 0.;}
};

#endif