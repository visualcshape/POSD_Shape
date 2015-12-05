//
// Created by VodalokLab on 2015/12/4.
//

#include "GraphicsModel.h"
#include "SimpleGraphics.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
#include "GraphicFactory.h"
#include "DescriptionVisitor.h"
#include <fstream>

#define ORIGINAL_X 0
#define ORIGINAL_Y 0
#define LENGTH 50
#define WIDTH 100
#define RADIUS 75

void GraphicsModel::addRectangleOnOriginalPoint() {
    Rectangle* rectangleToAdd = new Rectangle(ORIGINAL_X,ORIGINAL_Y,LENGTH,WIDTH);
    SimpleGraphics* graphicsToAdd = new SimpleGraphics(rectangleToAdd);
    this->pushBackGraphic(graphicsToAdd);
}

void GraphicsModel::addCircleOnOriginalPoint() {
    Circle* circleToAdd = new Circle(ORIGINAL_X,ORIGINAL_Y,RADIUS);
    SimpleGraphics* graphicsToAdd = new SimpleGraphics(circleToAdd);
    this->pushBackGraphic(graphicsToAdd);
}

void GraphicsModel::addSquareOnOriginalPoint() {
    Square* squareToAdd = new Square(ORIGINAL_X,ORIGINAL_Y,LENGTH);
    SimpleGraphics* graphicsToAdd = new SimpleGraphics(squareToAdd);
    this->pushBackGraphic(graphicsToAdd);
}

void GraphicsModel::setGraphicsVector(vector<Graphics *> *graphicVector) {
    vector<Graphics*>* deleteGraphicVector = _graphicsVector;
    _graphicsVector = graphicVector;
    delete deleteGraphicVector;
    Notify();
}

bool GraphicsModel::loadFile(const char *fileName) {
    GraphicsFactory factory;
    try{
        vector<Graphics*>* builtGraphicsVector = factory.buildMultiRootGraphicsFromFile(fileName);
        this->setGraphicsVector(builtGraphicsVector);
    }catch (std::string exceptionMessage){
        throw exceptionMessage;
    }
}

bool GraphicsModel::saveFile(const char *fileName) {
    std::fstream fileStream;
    fileStream.open(fileName,std::ios::out);
    for(vector<Graphics*>::iterator iterator = _graphicsVector->begin() ; iterator != _graphicsVector->end() ; iterator++){
        DescriptionVisitor descriptionVisitor;
        (*iterator)->accept(descriptionVisitor);
        fileStream << descriptionVisitor.getDescription();
    }

    fileStream.close();
}

Graphics* GraphicsModel::hitGraphic(QPointF pressPoint) {
    Graphics* hitGraphic = NULL;

    for(vector<Graphics*>::reverse_iterator iterator = _graphicsVector->rbegin() ; iterator != _graphicsVector->rend() ; iterator++){
        if(this->IsPointInGraphicBoundingBox((*iterator),pressPoint)){
            hitGraphic = (*iterator);
            break;
        }
    }

    changeSelectedGraphic(hitGraphic);
    Notify();
    return hitGraphic;
}
bool GraphicsModel::IsPointInGraphicBoundingBox(Graphics *graphics, QPointF point) {
    int pointX = (int)point.x();
    int pointY = (int)point.y();
    BoundingBox graphicBoundingBox = graphics->getBoundingBox();
    int boundingBoxLeftTopPointX = (int)graphicBoundingBox.llx();
    int boundingBoxLeftTopPointY = (int)graphicBoundingBox.lly();
    int boundingBoxRightBottomX = (int)graphicBoundingBox.urx();
    int boundingBoxRightBottomY = (int)graphicBoundingBox.ury();
    if(pointX >= boundingBoxLeftTopPointX && pointX <= boundingBoxRightBottomX && pointY >= boundingBoxLeftTopPointY && pointY <= boundingBoxRightBottomY)
        return true;
    else
        return false;
}

void GraphicsModel::changeSelectedGraphic(Graphics *graphic) {
    if(_selectedGraphic) {
        _selectedGraphic->setSelected(false);
    }
    if(graphic) {
        graphic->setSelected(true);
        _selectedGraphic = graphic;
    }else{
        _selectedGraphic = NULL;
    }
}

void GraphicsModel::pushBackGraphic(Graphics* graphicToPush) {
    if(_graphicsVector)
        _graphicsVector->push_back(graphicToPush);
    Notify();
}

void GraphicsModel::insertGraphicFromFront(Graphics *graphicToInsert) {
    if(_graphicsVector)
        _graphicsVector->insert(_graphicsVector->begin(),graphicToInsert);
    Notify();
}