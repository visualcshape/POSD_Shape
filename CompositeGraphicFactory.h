//
// Created by VodalokLab on 2015/10/29.
//

#ifndef HW2_COMPOSITEGRAPHICFACTORY_H
#define HW2_COMPOSITEGRAPHICFACTORY_H

#include "GraphicFactory.h"

class CompositeGraphicFactory : public GraphicsFactory{
protected:

public:
    CompositeGraphicFactory(){}
    virtual Graphics* createGraphic(string& content);
};


#endif //HW2_COMPOSITEGRAPHICFACTORY_H
