//
// Created by VodalokLab on 2015/12/10.
//

#include "AddCircleCommand.h"

AddCircleCommand::AddCircleCommand() {
    _addedGraphics = NULL;
}

void AddCircleCommand::Execute(GraphicsModel *model) {
    if(!_addedGraphics) {
        Graphics *addedCircle = model->addCircleOnOriginalPoint();
        _addedGraphics = addedCircle;
    }else{
        model->pushBackGraphic(_addedGraphics);
    }
}

void AddCircleCommand::Unexecute(GraphicsModel *model) {
    model->deleteGraphic(_addedGraphics,false);
}
