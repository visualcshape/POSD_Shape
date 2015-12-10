//
// Created by VodalokLab on 2015/12/10.
//

#include "AddSquareCommand.h"

AddSquareCommand::AddSquareCommand() {

}

void AddSquareCommand::Execute(GraphicsModel *model) {
    Graphics* addedSquare = model->addSquareOnOriginalPoint();
    _addedGraphics = addedSquare;
}

void AddSquareCommand::Unexecute(GraphicsModel *model) {
    model->deleteGraphic(_addedGraphics,false);
}
