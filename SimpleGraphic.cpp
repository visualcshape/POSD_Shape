#include "SimpleGraphics.h"

SimpleGraphics::SimpleGraphics(){
}

SimpleGraphics::SimpleGraphics(Shape* shape){
	_shape = shape;
	_boundingBox = _shape->getBoundingBox();
}