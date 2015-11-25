//
// Created by VodalokLab on 2015/10/29.
//

#ifndef HW2_SIMPLEGRAPHICFACTORY_H
#define HW2_SIMPLEGRAPHICFACTORY_H

#include "GraphicFactory.h"
#include "Rectangle.h"
#include "Square.h"
#include "Circle.h"

class SimpleGraphicFactory : public GraphicsFactory {
public:
    static Rectangle *createRectangle(string &graphicAttribute);
    static Square* createSquare(string& graphicAttribute);
    static Circle* createCircle(string& graphicAttribute);
protected:
public:
    SimpleGraphicFactory(){};

    virtual Graphics *createGraphic(string &content);
};


#endif //HW2_SIMPLEGRAPHICFACTORY_H
