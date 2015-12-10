//
// Created by VodalokLab on 2015/12/10.
//

#include "DeleteCommand.h"

DeleteCommand::DeleteCommand() {

}

void DeleteCommand::Execute(GraphicsModel *model) {
    if(!_deleteGraphic)
        _deleteGraphic = (*model->getSelectedGraphics())[0];
    model->deleteGraphic(_deleteGraphic,false);
    model->cleanUpHitGraphics();
}

void DeleteCommand::Unexecute(GraphicsModel *model) {
    model->pushBackGraphic(_deleteGraphic);
}
