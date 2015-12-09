#include <algorithm>
#include <math.h>
#include "CompositeGraphics.h"
#include <sstream>

using std::vector;

void CompositeGraphics::add(Graphics* graphic){
    graphic->increaseCompositeLevel();
	_graphics.push_back(graphic);
	calculateBoundingBox();
}

void CompositeGraphics::calculateBoundingBox(){
	_boundingBox = BoundingBox(0, 0, 0, 0);
	for (vector<Graphics*>::iterator iterator = _graphics.begin() ; iterator != _graphics.end(); iterator++){
		if (_boundingBox.area() == 0){
			_boundingBox = (*iterator)->getBoundingBox();
		}
		double newllx = min(_boundingBox.llx(), (*iterator)->getBoundingBox().llx());
		double newlly = min(_boundingBox.lly(), (*iterator)->getBoundingBox().lly());
		double newurx = max(_boundingBox.urx(), (*iterator)->getBoundingBox().urx());
		double newury = max(_boundingBox.ury(), (*iterator)->getBoundingBox().ury());
		double newW = fabs(newury - newlly);
		double newL = fabs(newurx - newllx);

		_boundingBox = BoundingBox(newllx, newlly, newL, newW);
	}
}

void CompositeGraphics::accept(GraphicsVisitor &visitor) {
	for(std::vector<Graphics*>::iterator itr = _graphics.begin()  ; itr != _graphics.end() ; itr++){
        (*itr)->accept(visitor);
    }
    visitor.visitCompositeGraphic(this);
}

double CompositeGraphics::calculateArea() {
    double retArea = 0.0;

    for(std::vector<Graphics*>::iterator itr = _graphics.begin() ; itr != _graphics.end() ; itr++){
        retArea += (*itr)->calculateArea();
    }

    return retArea;
}

string CompositeGraphics::getDescription() {
	stringstream ss;

	ss << "Comp R(" << _boundingBox.llx() << "," << _boundingBox.lly() << "," << _boundingBox.l() << "," << _boundingBox.w() << ")\n";

	return ss.str();
}

string CompositeGraphics::getDescription(int level) {
    stringstream ss;

    if(_compositeLevel!=level)
        return  "";

    for(int i = 0 ; i < level ; i++)
        ss << "  ";

    ss << "Comp R(" << _boundingBox.llx() << "," << _boundingBox.lly() << "," << _boundingBox.l() << "," << _boundingBox.w() << ")" << "\n";

    level++;

    for(vector<Graphics*>::iterator itr = _graphics.begin() ; itr != _graphics.end() ; itr++)
        ss << (*itr)->getDescription(level) ;

    return ss.str();
}

void CompositeGraphics::increaseCompositeLevel() {
    for(vector<Graphics*>::iterator itr = _graphics.begin() ; itr!=_graphics.end() ; itr++){
        (*itr)->increaseCompositeLevel();
    }
    this->_compositeLevel++;
}

void CompositeGraphics::draw(QGraphicsScene *scene) {
    QColor penColor(Qt::green);
    if(_selected)
        penColor = Qt::red;
    QPen pen(penColor,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    QBrush brush(QColor(0,0,0,0),Qt::SolidPattern);
    QRect boundingRect(((int)_boundingBox.llx()),((int)_boundingBox.lly()),((int)_boundingBox.l()),((int)_boundingBox.w()));
    scene->addRect(boundingRect,pen,brush);
    for(vector<Graphics*>::iterator itr = _graphics.begin() ; itr != _graphics.end() ; itr++)
        (*itr)->draw(scene);
}

void CompositeGraphics::setSelected(bool selected) {
    this->_selected = selected;
    for(vector<Graphics*>::iterator iterator = _graphics.begin() ; iterator!=_graphics.end() ; iterator++){
        (*iterator)->setSelected(selected);
    }
}

void CompositeGraphics::translation(QPoint translationLength) {
    for(vector<Graphics*>::iterator iterator = _graphics.begin() ; iterator!=_graphics.end() ; iterator++){
        (*iterator)->translation(translationLength);
    }
    this->calculateBoundingBox();
}

const vector<Graphics *> *CompositeGraphics::getContent() {
    return &this->_graphics;
}
