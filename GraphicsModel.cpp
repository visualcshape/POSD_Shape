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
#include <qdebug.h>
#include "CompositeGraphics.h"

#define ORIGINAL_X 0
#define ORIGINAL_Y 0
#define LENGTH 50
#define WIDTH 100
#define RADIUS 75

Graphics * GraphicsModel::addRectangleOnOriginalPoint() {
    Rectangle* rectangleToAdd = new Rectangle(ORIGINAL_X,ORIGINAL_Y,LENGTH,WIDTH);
    SimpleGraphics* graphicsToAdd = new SimpleGraphics(rectangleToAdd);
    this->insertGraphicFromFront(graphicsToAdd);
    return  graphicsToAdd;
}

Graphics * GraphicsModel::addCircleOnOriginalPoint() {
    Circle* circleToAdd = new Circle(ORIGINAL_X,ORIGINAL_Y,RADIUS);
    SimpleGraphics* graphicsToAdd = new SimpleGraphics(circleToAdd);
    this->insertGraphicFromFront(graphicsToAdd);
    return graphicsToAdd;
}

Graphics * GraphicsModel::addSquareOnOriginalPoint() {
    Square* squareToAdd = new Square(ORIGINAL_X,ORIGINAL_Y,LENGTH);
    SimpleGraphics* graphicsToAdd = new SimpleGraphics(squareToAdd);
    this->insertGraphicFromFront(graphicsToAdd);
    return  graphicsToAdd;
}

void GraphicsModel::setGraphicsVector(vector<Graphics *> *graphicVector) {
    vector<Graphics*>* deleteGraphicVector = _graphicsVector;
    _graphicsVector = graphicVector;
    //delete deleteGraphicVector;
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

Graphics * GraphicsModel::groupGraphics(vector<Graphics *> *graphicsToGroup) {
    Graphics* groupedGraphics = new CompositeGraphics();
    if(!graphicsToGroup)
        return NULL;
    for(vector<Graphics*>::reverse_iterator iterator = graphicsToGroup->rbegin() ; iterator != graphicsToGroup->rend() ; iterator++){
        groupedGraphics->addFromFront((*iterator));
        //Remove the graphics form model
        this->deleteGraphic((*iterator), false);
    }
    this->pushBackGraphic(groupedGraphics);
    Notify();
    return  groupedGraphics;
}

vector<Graphics*>* GraphicsModel::ungroupGraphic(Graphics *graphicToUngroup) {
    CompositeGraphics *compositeGraphicsToUngroup = dynamic_cast<CompositeGraphics*>(graphicToUngroup);
    //Only composite graphic can be ungroup... No change made...
    if(compositeGraphicsToUngroup==NULL)
        return NULL;
    vector<Graphics*>* compositeGraphics = compositeGraphicsToUngroup->getContent();

    for(vector<Graphics*>::iterator iterator = compositeGraphics->begin() ; iterator != compositeGraphics->end() ; iterator++){
        (*iterator)->decreaseCompositeLevel();
        this->pushBackGraphic((*iterator));
    }
    //Delete the composite graphic
    this->deleteGraphic(compositeGraphicsToUngroup, false);
    Notify();
    return  compositeGraphics;
}

void GraphicsModel::deleteGraphic(Graphics *graphicToDelete, bool deletePointer) {
    for(vector<Graphics*>::iterator iterator = this->_graphicsVector->begin() ; iterator != _graphicsVector->end() ; iterator++){
        if(*iterator == graphicToDelete){
            this->_graphicsVector->erase(iterator);
            if(deletePointer)
                delete (*iterator);
            break;
        }
    }
    Notify();
}

void GraphicsModel::addToSelectedGraphicsIfHit(QPointF pressPoint) {
    for(vector<Graphics*>::iterator iterator = _graphicsVector->begin() ; iterator != _graphicsVector->end() ; iterator++){
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

void GraphicsModel::describeModel() {
    DescriptionVisitor descriptionVisitor;
    for(vector<Graphics*>::iterator iterator = _graphicsVector->begin() ; iterator!=_graphicsVector->end() ; iterator++){
        (*iterator)->accept(descriptionVisitor);
    }
    qDebug() << descriptionVisitor.getDescription().c_str();
}

CompositeGraphics *GraphicsModel::hitCompositeGraphic(vector<Graphics*>* domain,QPointF point) {
    CompositeGraphics* ret = NULL;

    for(vector<Graphics*>::iterator iterator = domain->begin() ; iterator < domain->end() ; iterator++){
        if(IsPointInGraphicBoundingBox((*iterator),point)){
            CompositeGraphics* compositeGraphics = dynamic_cast<CompositeGraphics*>((*iterator));
            if(compositeGraphics) {
                ret = compositeGraphics;
                break;
            }
        }
    }

    changeFocusGraphic(ret);
    Notify();
    return  ret;
}

CompositeGraphics *GraphicsModel::getFocusedCompositeGraphic() {
    return _focusedCompositeGraphic;
}

CompositeGraphics *GraphicsModel::hitCompositeGraphic(CompositeGraphics *domain, QPointF point) {
    CompositeGraphics* ret = NULL;
    vector<Graphics*>* content = domain->getContent();

    for(vector<Graphics*>::iterator iterator = content->begin() ; iterator < content->end() ; iterator++){
        if(IsPointInGraphicBoundingBox((*iterator),point)){
            CompositeGraphics* compositeGraphics = dynamic_cast<CompositeGraphics*>((*iterator));
            if(compositeGraphics) {
                ret = compositeGraphics;
                break;
            }
        }
    }

    changeFocusGraphic(ret);
    Notify();
    return  ret;
}

void GraphicsModel::changeFocusGraphic(CompositeGraphics *changeToGraphic) {
    if(_focusedCompositeGraphic) {
        _focusedCompositeGraphic->setFocused(false);
        _focusedCompositeGraphic = changeToGraphic;
    }else{
        _focusedCompositeGraphic = changeToGraphic;
    }
    if(_focusedCompositeGraphic)
        _focusedCompositeGraphic->setFocused(true);

    Notify();
}

Graphics *GraphicsModel::hitGraphicInGraphicVector(vector<Graphics *> *graphicVector, QPointF position) {
    Graphics* ret = NULL;

    for(vector<Graphics*>::iterator iterator = graphicVector->begin() ; iterator < graphicVector->end() ; iterator++){
        if(IsPointInGraphicBoundingBox((*iterator),position)){
            ret = (*iterator);
            break;
        }
    }

    return ret;
}

void GraphicsModel::setGraphicBeFocused(Graphics *graphicsToSet, bool focused) {
    if(focused)
        _graphicBeFocus = graphicsToSet;
    graphicsToSet->setFocused(focused);
    Notify();
}

Graphics *GraphicsModel::getGraphicBeFocus() {
    return _graphicBeFocus;
}

void GraphicsModel::cleanGraphicBeFocus() {
    if(_graphicBeFocus){
        _graphicBeFocus->setFocused(false);
        _graphicBeFocus = NULL;
    }
    Notify();
}

void GraphicsModel::moveGraphicUpInVector(vector<Graphics *> *content, Graphics* moveGraphics) {
    int indexInContent = find(content->begin(),content->end(),moveGraphics) - content->begin();
    if(indexInContent == 0 || content->size() < 1 || indexInContent >= content->size())
        return;
    iter_swap(content->begin()+indexInContent,content->begin()+indexInContent-1);
    Notify();
}

void GraphicsModel::moveGraphicDownInVector(vector<Graphics *> *content, Graphics* moveGraphics) {
    int indexInContent = find(content->begin(),content->end(),moveGraphics) - content->begin();
    if(indexInContent == content->size()-1 || content->size() < 1 || indexInContent >= content->size())
        return;
    iter_swap(content->begin()+indexInContent,content->begin()+indexInContent+1);
    Notify();
}

CompositeGraphics *GraphicsModel::updateGraphics(CompositeGraphics *graphicsToUpdate) {
    CompositeGraphics* ret = NULL;

    for(vector<Graphics*>::iterator iterator = _graphicsVector->begin() ; iterator < _graphicsVector->end() ; iterator++){
        CompositeGraphics* compositeGraphics = dynamic_cast<CompositeGraphics*>((*iterator));
        if(!compositeGraphics){
            continue;
        }
        Graphics* sample = (*graphicsToUpdate->getContent())[0];
        //not this composite -> keep
        ret = findCompositeInGraphics(compositeGraphics, sample);
    }

    return ret;
}

CompositeGraphics *GraphicsModel::findCompositeInGraphics(CompositeGraphics *compositeGraphics, Graphics *sample) {
    CompositeGraphics* graphics = NULL;
    vector<Graphics*>* content = compositeGraphics->getContent();
    for(vector<Graphics*>::iterator iterator = content->begin() ; iterator < content->end() ; iterator++){
        if((*iterator)==sample){
            return compositeGraphics;
        }
        CompositeGraphics* innerComposite = dynamic_cast<CompositeGraphics*>((*iterator));
        if(!innerComposite){
            continue;
        }
        graphics = findCompositeInGraphics(innerComposite,sample);
    }

    return graphics;
}
