//
// Created by VodalokLab on 2015/12/10.
//

#include "AddRectangleCommand.h"

AddRectangleCommand::AddRectangleCommand() {
    _addedGraphic = NULL;
}

void AddRectangleCommand::Execute(GraphicsModel *model) {
    if(!_addedGraphic) {
        Graphics *addedRectangle = model->addRectangleOnOriginalPoint();
        _addedGraphic = addedRectangle;
    }else{
        model->pushBackGraphic(_addedGraphic);
    }
}

void AddRectangleCommand::Unexecute(GraphicsModel *model) {
    model->deleteGraphic(_addedGraphic,false);
}
