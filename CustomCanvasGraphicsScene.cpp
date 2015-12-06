//
// Created by Vodalok on 2015/12/5.
//

#include "CustomCanvasGraphicsScene.h"
#include <QDrag>
#include <QMimeData>
#include <QDebug>
#include <QApplication>

CustomCanvasGraphicsScene::CustomCanvasGraphicsScene(GraphicsModel *graphicsModel) : _graphicsModel(graphicsModel),_dragging(false),_hasGraphicDragging(false) {

}

void CustomCanvasGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Mouse click on scene : (" << event->scenePos().x() << "," << event->scenePos().y() << ")";
    if(event->button() == Qt::LeftButton) {
        event->accept();
        _dragStartPosition = event->scenePos();
        _graphicsModel->hitGraphic(event->scenePos());
    }
    QGraphicsScene::mousePressEvent(event);
}

void CustomCanvasGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    const int START_DRAG_THRESHOLD = 10;
    Graphics* hitGraphic = NULL;
    if(!(event->buttons() & Qt::LeftButton))
        return;
    if((event->scenePos() - _dragStartPosition).manhattanLength() < START_DRAG_THRESHOLD)
        return;
    if(!_dragging && !_hasGraphicDragging) {
        hitGraphic = _graphicsModel->hitGraphic(event->scenePos());
        _dragging = true;
    }
    if(!hitGraphic && !_hasGraphicDragging){
        _dragging = false;
        return;
    }
    event->accept();
    _dragging = true;
    _hasGraphicDragging = true;
    _graphicsModel->translationGraphic(_graphicsModel->getSelectedGraphic(),QPoint((event->scenePos()-_dragStartPosition).toPoint()));
    _dragStartPosition = event->scenePos();

    QGraphicsScene::mouseMoveEvent(event);
}

void CustomCanvasGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    _dragging = false;
    _hasGraphicDragging = false;
    QGraphicsScene::mouseReleaseEvent(event);
}
