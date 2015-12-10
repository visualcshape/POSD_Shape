//
// Created by VodalokLab on 2015/12/10.
//

#include "AddRectangleCommand.h"

AddRectangleCommand::AddRectangleCommand() {

}

void AddRectangleCommand::Execute(GraphicsModel *model) {
    Graphics* addedRectangle = model->addRectangleOnOriginalPoint();
    _addedGraphic = addedRectangle;
}

void AddRectangleCommand::Unexecute(GraphicsModel *model) {
    model->deleteGraphic(_addedGraphic,false);
}
