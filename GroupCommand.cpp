//
// Created by VodalokLab on 2015/12/10.
//

#include "GroupCommand.h"

GroupCommand::GroupCommand() {

}

void GroupCommand::Execute(GraphicsModel *model) {
    _graphicsToGroup = *model->getSelectedGraphics();

    _groupedGraphic = model->groupGraphics(&_graphicsToGroup);

    model->cleanUpHitGraphics();
}

void GroupCommand::Unexecute(GraphicsModel *model) {
    model->ungroupGraphic(_groupedGraphic);
}
