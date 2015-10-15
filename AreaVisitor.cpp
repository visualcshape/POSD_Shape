//
// Created by Chi-Chia Sun on 2015/10/16.
//

#include "AreaVisitor.h"
#include "Graphics.h"

void AreaVisitor::visitCompositeGraphic(Graphics *graphics) {
    _area += graphics->calculateArea();
}

void AreaVisitor::visitSimpleGraphic(Graphics *graphics) {
    _area += graphics->calculateArea();
}

AreaVisitor::AreaVisitor():_area(0){

}

double AreaVisitor::area() {
    return _area;
}
