#include <algorithm>
#include <math.h>
#include "CompositeGraphics.h"

void CompositeGraphics::add(Graphics* graphic){
	_graphics.push_back(graphic);
	calculateBoundingBox();
}

void CompositeGraphics::calculateBoundingBox(){
	//_boundingBox = BoundingBox(0, 0, 0, 0);
	for (vector<Graphics*>::iterator iterator = _graphics.begin(); iterator != _graphics.end(); iterator++){
		if (_boundingBox.area() == 0){
			_boundingBox = (*iterator)->getBoundingBox();
		}
		double newllx = min(_boundingBox.llx(), (*iterator)->getBoundingBox().llx());
		double newlly = min(_boundingBox.lly(), (*iterator)->getBoundingBox().lly());
		double newurx = max(_boundingBox.urx(), (*iterator)->getBoundingBox().urx());
		double newury = max(_boundingBox.urx(), (*iterator)->getBoundingBox().ury());
		double newW = fabs(newury - newlly);
		double newL = fabs(newurx - newllx);

		_boundingBox = BoundingBox(newllx, newlly, newL, newW);
	}
}
