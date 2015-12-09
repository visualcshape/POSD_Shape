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
#include <iostream>
#include "CompositeGraphics.h"

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

void GraphicsModel::translationGraphic(Graphics *graphicToTranslate, QPoint translationLength) {
    if(_graphicsVector){
        //ensure the graphic is exist in vector
        if(std::find(_graphicsVector->begin(),_graphicsVector->end(),graphicToTranslate)!=_graphicsVector->end()){
            graphicToTranslate->translation(translationLength);
        }
    }
    Notify();
}

Graphics *GraphicsModel::getSelectedGraphic() {
    return _selectedGraphic;
}

void GraphicsModel::groupGraphics(vector<Graphics *> &graphicsToGroup) {
    Graphics* groupedGraphics = new CompositeGraphics();
    for(vector<Graphics*>::iterator iterator = graphicsToGroup.begin() ; iterator != graphicsToGroup.end() ; iterator++){
        groupedGraphics->add((*iterator));
        //Remove the graphics form model
        this->deleteGraphic((*iterator));
    }
    this->pushBackGraphic(groupedGraphics);
    Notify();
}

void GraphicsModel::ungroupGraphic(Graphics *graphicToUngroup) {
    CompositeGraphics *compositeGraphicsToUngroup = dynamic_cast<CompositeGraphics*>(graphicToUngroup);
    //Only composite graphic can be ungroup... No change made...
    if(compositeGraphicsToUngroup==NULL)
        return;
    const vector<Graphics*>* compositeGraphics = compositeGraphicsToUngroup->getContent();

    for(vector<Graphics*>::const_iterator iterator = compositeGraphics->begin() ; iterator != compositeGraphics->end() ; iterator++){
        this->pushBackGraphic((*iterator));
    }
    //Delete the composite graphic
    this->deleteGraphic(compositeGraphicsToUngroup);
    Notify();
}

void GraphicsModel::deleteGraphic(Graphics *graphicToDelete) {
    for(vector<Graphics*>::iterator iterator = this->_graphicsVector->begin() ; iterator != _graphicsVector->end() ; iterator++){
        if(*iterator == graphicToDelete){
            this->_graphicsVector->erase(iterator);
            delete (*iterator);
            break;
        }
    }
    Notify();
}

void GraphicsModel::addToSelectedGraphicsIfHit(QPointF pressPoint) {
    for(vector<Graphics*>::reverse_iterator iterator = _graphicsVector->rbegin() ; iterator != _graphicsVector->rend() ; iterator++){
        if(this->IsPointInGraphicBoundingBox((*iterator),pressPoint)){
            //if added don't add again...
            if(std::find(_selectedGraphics->begin(),_selectedGraphics->end(),*iterator)!=_selectedGraphics->end()){
                break;
            }
            _selectedGraphics->push_back((*iterator));
            (*iterator)->setSelected(true);
            break;
        }
    }

    Notify();
}

void GraphicsModel::cleanUpHitGraphics() {
    for(vector<Graphics*>::iterator iterator = _selectedGraphics->begin() ; iterator != _selectedGraphics->end() ; iterator++){
        (*iterator)->setSelected(false);
    }
    this->_selectedGraphics->clear();
    Notify();
}

vector<Graphics *> *GraphicsModel::getSelectedGraphics() {
    return _selectedGraphics;
}

void GraphicsModel::translationSelectedGraphics(QPoint translationLength) {
    if(_selectedGraphics && _graphicsVector){
        //ensure the graphic is exist in vector
        for(vector<Graphics*>::iterator iterator = _selectedGraphics->begin() ; iterator != _selectedGraphics->end() ; iterator++){
            (*iterator)->translation(translationLength);
        }
    }
    Notify();
}

bool GraphicsModel::isHitSelectedGraphicBoundingBox(QPointF pressPoint) {
    for(vector<Graphics*>::reverse_iterator iterator = _selectedGraphics->rbegin() ; iterator != _selectedGraphics->rend() ; iterator++){
        if(this->IsPointInGraphicBoundingBox((*iterator),pressPoint)){
            return  true;
        }
    }
}
