//
// Created by VodalokLab on 2015/12/4.
//

#include "GraphicsModel.h"
#include "SimpleGraphics.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
#include "GraphicFactory.h"

#define ORIGINAL_X 0
#define ORIGINAL_Y 0
#define LENGTH 50
#define WIDTH 100
#define RADIUS 75

void GraphicsModel::addRectangleOnOriginalPoint() {
    Rectangle* rectangleToAdd = new Rectangle(ORIGINAL_X,ORIGINAL_Y,LENGTH,WIDTH);
    SimpleGraphics* graphicToAdd = new SimpleGraphics(rectangleToAdd);
    _graphicsVector->push_back(graphicToAdd);
    Notify();
}

void GraphicsModel::addCircleOnOriginalPoint() {
    Circle* circleToAdd = new Circle(ORIGINAL_X,ORIGINAL_Y,RADIUS);
    SimpleGraphics* graphicsToAdd = new SimpleGraphics(circleToAdd);
    _graphicsVector->push_back(graphicsToAdd);
    Notify();
}

void GraphicsModel::addSquareOnOriginalPoint() {
    Square* squareToAdd = new Square(ORIGINAL_X,ORIGINAL_Y,LENGTH);
    SimpleGraphics* graphicsToAdd = new SimpleGraphics(squareToAdd);
    _graphicsVector->push_back(graphicsToAdd);
    Notify();
}

bool GraphicsModel::loadFile(const char *fileName) {
    GraphicsFactory factory;
    try{
        vector<Graphics*>* builtGraphicsVector = factory.buildMultiRootGraphicsFromFile(fileName);
        this->setGraphicsVector(builtGraphicsVector);
    }catch (std::string exceptionMessage){

    }
}