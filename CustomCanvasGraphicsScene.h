//
// Created by Vodalok on 2015/12/5.
//

#ifndef HW2_CUSTOMCANVASGRAPHICSVIEW_H
#define HW2_CUSTOMCANVASGRAPHICSVIEW_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include "GraphicsModel.h"
#include "PresentationModel.h"

class CustomCanvasGraphicsScene : public QGraphicsScene {
private:
    GraphicsModel* _graphicsModel;
    PresentationModel* _presentationModel;
    //Drag
    QPointF _dragStartPosition;
    bool _draggingGraphics;
    bool _multiSelected;

    void checkUngroupCanEnable();
public:
    CustomCanvasGraphicsScene(GraphicsModel* graphicsModel, PresentationModel* presentationModel);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};


#endif //HW2_CUSTOMCANVASGRAPHICSVIEW_H
