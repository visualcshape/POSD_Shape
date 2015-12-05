//
// Created by Vodalok on 2015/12/5.
//

#include "CustomCanvasGraphicsScene.h"
#include <iostream>

void CustomCanvasGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    std::cout << "Mouse click on scene : (" << event->scenePos().x() << "," << event->scenePos().y() << ")" << std::endl;

}

void CustomCanvasGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {

}

void CustomCanvasGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {

}

void CustomCanvasGraphicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {

}
