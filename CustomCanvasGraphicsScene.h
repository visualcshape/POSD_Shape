//
// Created by Vodalok on 2015/12/5.
//

#ifndef HW2_CUSTOMCANVASGRAPHICSVIEW_H
#define HW2_CUSTOMCANVASGRAPHICSVIEW_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include "GraphicsModel.h"

class CustomCanvasGraphicsScene : public QGraphicsScene {
private:
    GraphicsModel* _graphicsModel;

    //Drag
    QPointF _dragStartPosition;
public:
    CustomCanvasGraphicsScene(GraphicsModel* graphicsModel);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
};


#endif //HW2_CUSTOMCANVASGRAPHICSVIEW_H
