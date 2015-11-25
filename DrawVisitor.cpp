//
// Created by VodalokLab on 2015/11/25.
//

#include "DrawVisitor.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"

DrawVisitor::DrawVisitor(QGraphicsScene* scene){
    _scene = scene;
}

void DrawVisitor::visitCompositeGraphic(Graphics *graphics) {
    graphics->draw(_scene);
}

void DrawVisitor::visitSimpleGraphic(Graphics *graphics) {
    graphics->draw(_scene);
}
