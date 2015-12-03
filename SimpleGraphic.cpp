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
    string description =  _shape->describe();
    string graphicType = "";
    string graphicAttribute = "";
    string token = "";
    const char DELIM = '(';
    stringstream tokenStringStream(description);
    std::getline(tokenStringStream, token, DELIM);
    graphicType = token;
    Utility::deleteSpace(graphicType);
    std::getline(tokenStringStream,token, DELIM);

    //remove right brace
    token.erase(token.length()-1,1);
    graphicAttribute = token;

    QPen pen(Qt::blue,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    QBrush brush(QColor(0,0,0,0),Qt::SolidPattern);
    switch(graphicType[0]){
        case 'R':{
            Rectangle* pRectangle = SimpleGraphicFactory::createRectangle(graphicAttribute);
            QRect* rect = new QRect(pRectangle->positionPoint.getX(), pRectangle->positionPoint.getY(), pRectangle->width, pRectangle->height);
            scene->addRect(*rect,pen,brush);
        }
            break;
        case 'C':{
            Circle* circle = SimpleGraphicFactory::createCircle(graphicAttribute);
            QRect* rect = new QRect(circle->centerX - circle->radius, circle->centerY - circle->radius, circle->radius * 2, circle->radius * 2);
            scene->addEllipse(*rect,pen,brush);
        }
            break;
        case 'S':{
            Square* square = SimpleGraphicFactory::createSquare(graphicAttribute);
            QRect* rect = new QRect(square->x, square->y, square->length, square->length);
            scene->addRect(*rect,pen,brush);
        }
            break;
    }

}
