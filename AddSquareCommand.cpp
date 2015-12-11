//
// Created by VodalokLab on 2015/12/10.
//

#include "AddSquareCommand.h"

AddSquareCommand::AddSquareCommand() {
    _addedGraphics = NULL;
}

void AddSquareCommand::Execute(GraphicsModel *model) {
    if(!_addedGraphics){
        Graphics* addedSquare = model->addSquareOnOriginalPoint();
        _addedGraphics = addedSquare;
    }else{
        model->pushBackGraphic(_addedGraphics);
    }
}

void AddSquareCommand::Unexecute(GraphicsModel *model) {
    model->deleteGraphic(_addedGraphics,false);
}
