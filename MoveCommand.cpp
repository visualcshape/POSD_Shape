//
// Created by VodalokLab on 2015/12/10.
//

#include "MoveCommand.h"

void MoveCommand::Execute(GraphicsModel *model) {
    if(_movedGraphics.size() == 0)
        _movedGraphics = *model->getSelectedGraphics();
    if(!_firstMove)
        for(vector<Graphics*>::iterator iterator = _movedGraphics.begin() ; iterator != _movedGraphics.end() ; iterator++){
            (*iterator)->translation((_endPoint-_startPoint).toPoint());
        }
    _firstMove = false;
}

void MoveCommand::Unexecute(GraphicsModel *model) {
    for(vector<Graphics*>::iterator iterator = _movedGraphics.begin() ; iterator != _movedGraphics.end() ; iterator++){
        (*iterator)->translation((_startPoint-_endPoint).toPoint());
    }
}

MoveCommand::MoveCommand():_firstMove(true) {

}
