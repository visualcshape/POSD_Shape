#include "SimpleGraphics.h"
#include <sstream>
#include "utility.h"
#include "shape.h"
#include "SimpleGraphicFactory.h"

using namespace std;

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
	if(this->_compositeLevel > 0)
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

void SimpleGraphics::draw(QGraphicsScene *scene) {
    //Pen Configuration
    QColor penColor = Qt::blue;
    const int PEN_WIDTH = 3;
    const Qt::PenStyle PEN_STYLE = Qt::SolidLine;
    const Qt::PenCapStyle PEN_CAP_STYLE = Qt::SquareCap;
    const Qt::PenJoinStyle PEN_JOIN_STYLE = Qt::RoundJoin;
    //Brush Configuration
    const QColor BRUSH_COLOR = QColor(0, 0, 0, 0);
    const Qt::BrushStyle BRUSH_STYLE = Qt::NoBrush;
    //Draw on scene
    if(_selected)
        penColor = Qt::darkRed;
    QPen pen(penColor, PEN_WIDTH, PEN_STYLE, PEN_CAP_STYLE, PEN_JOIN_STYLE);
    QBrush brush(BRUSH_COLOR, BRUSH_STYLE);
    BoundingBox shapeBoundingBox = _shape->getBoundingBox();
    QPoint rectPosition(shapeBoundingBox.llx(), shapeBoundingBox.lly());
    QSize rectSize(shapeBoundingBox.l(), shapeBoundingBox.w());
    QRect drawRectangle(rectPosition,rectSize);
    //Dynamic cast used to decide the concrete shape of shape.
    Circle* castCircle = dynamic_cast<Circle*>(_shape);
    if(castCircle != NULL){
        scene->addEllipse(drawRectangle,pen,brush);
        return;
    }
    scene->addRect(drawRectangle,pen,brush);
}

void SimpleGraphics::translation(QPoint translationLength) {
    _shape->translation(translationLength);
    _boundingBox = _shape->getBoundingBox();
}
