//
// Created by VodalokLab on 2015/10/29.
//

#include "CompositeGraphicFactory.h"
#include "CompositeGraphics.h"

Graphics *CompositeGraphicFactory::createGraphic(string& cotent) {
    return new CompositeGraphics();
}
