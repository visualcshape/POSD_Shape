//
// Created by Chi-Chia Sun on 2015/10/16.
//

#ifndef HW2_AREA_VISITOR_H
#define HW2_AREA_VISITOR_H

#include "GraphicsVisitor.h"

class AreaVisitor : public GraphicsVisitor {
private:
    double _area;
public:
    AreaVisitor();

    void visitCompositeGraphic(Graphics *graphics);
    void visitSimpleGraphic(Graphics *graphics);

    double area();
};


#endif //HW2_AREAVISITOR_H
