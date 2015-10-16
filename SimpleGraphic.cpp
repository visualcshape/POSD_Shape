#include "SimpleGraphics.h"

SimpleGraphics::SimpleGraphics(){
}

SimpleGraphics::SimpleGraphics(Shape* shape){
	_shape = shape;
	_boundingBox = _shape->getBoundingBox();
}

void SimpleGraphics::accept(GraphicsVisitor &graphicVisitor) {
	graphicVisitor.visitSimpleGraphic(this);
}

double SimpleGraphics::calculateArea() {
    return _shape->area();
}

string SimpleGraphics::getDescription() {
	if(this->isComposited)
		return "";
	return _shape->describe() + "\n";
}

string SimpleGraphics::getDescription(int level) {
	std::string ret = "";

	for(int i = 0 ; i < level ; i++)
		ret += "  ";
	ret += _shape->describe();
	ret += "\n";
	return ret;
}

void SimpleGraphics::increaseCompositeLevel() {
	_compositeLevel++;
}
