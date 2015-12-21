//
// Created by Vodalok on 2015/12/21.
//

#include "SetAllGraphicsFocusToFalseVisitor.h"

void SetAllGraphicsFocusToFalseVisitor::visitCompositeGraphic(Graphics *graphics) {
    graphics->setFocused(false);
}

void SetAllGraphicsFocusToFalseVisitor::visitSimpleGraphic(Graphics *graphics) {
    graphics->setFocused(false);
}
