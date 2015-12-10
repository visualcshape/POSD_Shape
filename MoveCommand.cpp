//
// Created by VodalokLab on 2015/12/10.
//

#include "MoveCommand.h"

void MoveCommand::Execute(GraphicsModel *model) {
    //Don't do anything...
}

void MoveCommand::Unexecute(GraphicsModel *model) {

}

MoveCommand::MoveCommand() {

}

void MoveCommand::ExecuteEnd(GraphicsModel *model) {

}

void MoveCommand::ExecuteStart(GraphicsModel *model) {
    _movedGraphics = *model->getSelectedGraphics();
    for(vector<Graphics*>::iterator iterator = _movedGraphics.begin() ; iterator != _movedGraphics.end() ; iterator++){
        
    }
}
