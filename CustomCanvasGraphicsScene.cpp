//
// Created by Vodalok on 2015/12/5.
//

#include "CustomCanvasGraphicsScene.h"
#include <QDrag>
#include <QMimeData>
#include <QDebug>
#include <QApplication>

CustomCanvasGraphicsScene::CustomCanvasGraphicsScene(GraphicsModel *graphicsModel) : _graphicsModel(graphicsModel),
                                                                                     _draggingGraphics(false),
                                                                                     _multiSelected(false)
{

}

void CustomCanvasGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Mouse click on scene : (" << event->scenePos().x() << "," << event->scenePos().y() << ")";
    _dragStartPosition = event->scenePos();
    if(event->button() == Qt::LeftButton && QGuiApplication::keyboardModifiers() == Qt::CTRL){
        event->accept();
        _graphicsModel->addToSelectedGraphicsIfHit(event->scenePos());
        if(_graphicsModel->getSelectedGraphics()->size() > 1)
            _multiSelected = true;
        else
            _multiSelected = false;
    } else if(event->button() == Qt::LeftButton) {
        event->accept();
        if(!_graphicsModel->isHitSelectedGraphicBoundingBox(event->scenePos())){
            _graphicsModel->cleanUpHitGraphics();
            _graphicsModel->addToSelectedGraphicsIfHit(event->scenePos());
            _multiSelected = false;
        }

    }

    QGraphicsScene::mousePressEvent(event);
}

void CustomCanvasGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    //Dragging
    const int START_DRAG_THRESHOLD = 10;
    if(!(event->buttons() & Qt::LeftButton))
        return;
    if((event->scenePos() - _dragStartPosition).manhattanLength() < START_DRAG_THRESHOLD)
        return;
    //Not in multi-selected mode
    //if(!_draggingGraphics && !_multiSelected)
    //    _graphicsModel->addToSelectedGraphicsIfHit(event->scenePos());
    if(_graphicsModel->getSelectedGraphics()->size() == 0) {
        _draggingGraphics = false;
        return;
    }
    event->accept();
    _draggingGraphics = true;
    _graphicsModel->translationSelectedGraphics(QPoint((event->scenePos()-_dragStartPosition).toPoint()));
    _dragStartPosition = event->scenePos();

    QGraphicsScene::mouseMoveEvent(event);
}

void CustomCanvasGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    _draggingGraphics = false;
    QGraphicsScene::mouseReleaseEvent(event);
}
