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
