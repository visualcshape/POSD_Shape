//
// Created by VodalokLab on 2015/10/16.
//

#include "DescriptionVisitor.h"

void DescriptionVisitor::visitCompositeGraphic(Graphics *graphics) {
    _desc += graphics->getDescription(0);
    //_desc += "\n";
}

void DescriptionVisitor::visitSimpleGraphic(Graphics *graphics) {
    _desc += graphics->getDescription();
    //_desc += "\n";
}

std::string DescriptionVisitor::getDescription() {
    return _desc;
}
