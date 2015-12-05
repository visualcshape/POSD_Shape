//
// Created by Vodalok on 2015/12/5.
//

#include "CustomCanvasGraphicsScene.h"
#include <QDrag>
#include <QMimeData>
#include <QDebug>
#include <QApplication>

CustomCanvasGraphicsScene::CustomCanvasGraphicsScene(GraphicsModel *graphicsModel) : _graphicsModel(graphicsModel) {

}

void CustomCanvasGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);
    qDebug() << "Mouse click on scene : (" << event->scenePos().x() << "," << event->scenePos().y() << ")";
    if(event->button() == Qt::LeftButton)
        _dragStartPosition = event->scenePos();
    _graphicsModel->hitGraphic(event->scenePos());
}

void CustomCanvasGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    QGraphicsScene::dragEnterEvent(event);
    qDebug() << "Drag Start...";
    event->accept();
    event->acceptProposedAction();

}

void CustomCanvasGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    QGraphicsScene::dragMoveEvent(event);
    qDebug() << "Dragging...";
    event->accept();
    event->acceptProposedAction();
}

void CustomCanvasGraphicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    QGraphicsScene::dragLeaveEvent(event);
    qDebug() << "Drag end";
    event->accept();
    event->proposedAction();
}

void CustomCanvasGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    const int START_DRAG_THRESHOLD = 10;
    if(!(event->buttons() & Qt::LeftButton))
        return;
    if((event->scenePos() - _dragStartPosition).manhattanLength() < START_DRAG_THRESHOLD)
        return;
    event->accept();

    QDrag *drag = new QDrag(this);
    CustomCanvasGraphicsScene *thisItem = this;
    QByteArray byteArray(reinterpret_cast<char *>(&thisItem), sizeof(CustomCanvasGraphicsScene *));
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("CustomCanvasGraphicsScene", byteArray);
    drag->setMimeData(mimeData);
    drag->start();
    QGraphicsScene::mouseMoveEvent(event);
}

void CustomCanvasGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);

}
