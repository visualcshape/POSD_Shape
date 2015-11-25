//
// Created by VodalokLab on 2015/11/25.
//

#ifndef HW2_DRAWVISITOR_H
#define HW2_DRAWVISITOR_H

#include "GraphicsVisitor.h"
#include "Graphics.h"
#include <QGraphicsScene>

class DrawVisitor : public  GraphicsVisitor{
private:
    QGraphicsScene* _scene;
public:
    DrawVisitor(QGraphicsScene* scene);
    virtual void visitCompositeGraphic(Graphics *graphics);
    virtual void visitSimpleGraphic(Graphics* graphics);
};


#endif //HW2_DRAWVISITOR_H
