//
// Created by VodalokLab on 2015/12/10.
//

#include "AddCircleCommand.h"

AddCircleCommand::AddCircleCommand() {

}

void AddCircleCommand::Execute(GraphicsModel *model) {
    Graphics* addedCircle = model->addCircleOnOriginalPoint();
    _addedGraphics = addedCircle;
}

void AddCircleCommand::Unexecute(GraphicsModel *model) {
    model->deleteGraphic(_addedGraphics,false);
}
