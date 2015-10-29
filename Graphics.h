#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_
#include <string>
#include "BoundingBox.h"
#include "GraphicsVisitor.h"

using std::string;

class Graphics{
protected:
	BoundingBox _boundingBox;
	int _compositeLevel;
public:
	Graphics():_boundingBox(0,0,0,0),_compositeLevel(0){}

	virtual BoundingBox getBoundingBox(){ return _boundingBox; }
	
	virtual void add(Graphics* graphic){ throw std::string("Cannot add child"); }

	virtual void accept(GraphicsVisitor &graphicVisitor) {};

	virtual double calculateArea(){return 0.;}

	virtual  string getDescription() {return "";}

	virtual string getDescription(int level){return "";}

	virtual  int getCompositeLevel(){return _compositeLevel;}

	virtual void increaseCompositeLevel() {_compositeLevel++;}
};

#endif