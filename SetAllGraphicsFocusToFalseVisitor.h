//
// Created by Vodalok on 2015/12/21.
//

#ifndef HW2_SETALLGRAPHICSFOCUSVISITOR_H
#define HW2_SETALLGRAPHICSFOCUSVISITOR_H

#include "GraphicsVisitor.h"
#include "Graphics.h"

class SetAllGraphicsFocusToFalseVisitor : public GraphicsVisitor{
private:
public:
    SetAllGraphicsFocusToFalseVisitor(){}

    void visitCompositeGraphic(Graphics* graphics);

    void visitSimpleGraphic(Graphics* graphics);
};


#endif //HW2_SETALLGRAPHICSFOCUSVISITOR_H
