//
// Created by Vodalok on 2015/12/5.
//

#include "CustomCanvasGraphicsScene.h"
#include <QDrag>
#include <QMimeData>
#include <QDebug>
#include <QApplication>
#include "CompositeGraphics.h"
#include "CommandManager.h"

CustomCanvasGraphicsScene::CustomCanvasGraphicsScene(GraphicsModel *graphicsModel,PresentationModel *presentationModel) : _graphicsModel(graphicsModel),
                                                                                     _draggingGraphics(false),
                                                                                     _multiSelected(false),
                                                                                     _presentationModel(presentationModel)
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
    _presentationModel->SetGroupEnabled(_multiSelected);

    checkUngroupCanEnable();

    checkDeleteButtonCanEnable();

    checkMoveUpDownCanEnable();

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
    if(_graphicsModel->getSelectedGraphics()->size() == 0) {
        _draggingGraphics = false;
        return;
    }
    event->accept();
    if(!_draggingGraphics){
        //Execute Command
        _moveCommand = new MoveCommand();
        _moveCommand->SetStartPoint(event->scenePos());
    }
    _draggingGraphics = true;
    _graphicsModel->translationSelectedGraphics(QPoint((event->scenePos()-_dragStartPosition).toPoint()));
    _dragStartPosition = event->scenePos();

    QGraphicsScene::mouseMoveEvent(event);
}

void CustomCanvasGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if(_draggingGraphics){
        CommandManager* instance = CommandManager::instance();
        _moveCommand->SetEndPoint(event->scenePos());
        instance->Execute(_moveCommand);
    }
    _draggingGraphics = false;
    QGraphicsScene::mouseReleaseEvent(event);
    
}

void CustomCanvasGraphicsScene::checkUngroupCanEnable() {
    if(!_multiSelected && _graphicsModel->getSelectedGraphics()->size() > 0){
        Graphics* graphics = (*_graphicsModel->getSelectedGraphics())[0];

        if(dynamic_cast<CompositeGraphics*>(graphics))
            _presentationModel->SetUngroupEnabled(true);
        else
            _presentationModel->SetUngroupEnabled(false);
    }else{
        _presentationModel->SetUngroupEnabled(false);
    }
}

void CustomCanvasGraphicsScene::checkDeleteButtonCanEnable() {
    if(_graphicsModel->getSelectedGraphics()->size() == 1)
        _presentationModel->SetDeleteGraphicEnabled(true);
    else
        _presentationModel->SetDeleteGraphicEnabled(false);
}

void CustomCanvasGraphicsScene::checkMoveUpDownCanEnable() {
    if(_graphicsModel->getSelectedGraphics()->size()==1) {
        CompositeGraphics* selectedCompositeGraphic = dynamic_cast<CompositeGraphics*>((*_graphicsModel->getSelectedGraphics())[0]);
        if(selectedCompositeGraphic == NULL) {
            _presentationModel->SetMoveDownEnabled(false);
            _presentationModel->SetMoveUpEnabled(false);
        }
        else{
            _presentationModel->SetMoveDownEnabled(true);
            _presentationModel->SetMoveUpEnabled(true);
        }
    }else{
        _presentationModel->SetMoveUpEnabled(false);
        _presentationModel->SetMoveDownEnabled(false);
    }
}

void CustomCanvasGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
        qDebug() << "Double Clicked..";
        Graphics *focusedGraphics = _graphicsModel->focusGraphic(event->scenePos());
        CompositeGraphics *selectCompositeGraphic = dynamic_cast<CompositeGraphics*>(focusedGraphics);
        if(!selectCompositeGraphic)
            return;

    }

    QGraphicsScene::mouseDoubleClickEvent(event);
}
