//
// Created by VodalokLab on 2015/12/10.
//

#include "UngroupCommand.h"

UngroupCommand::UngroupCommand() {

}

void UngroupCommand::Execute(GraphicsModel *model) {
    _graphicToUngroup = (*model->getSelectedGraphics())[0];
    _ungropupedGraphics = *model->ungroupGraphic(_graphicToUngroup);
    model->cleanUpHitGraphics();
}

void UngroupCommand::Unexecute(GraphicsModel *model) {
    model->groupGraphics(&_ungropupedGraphics);
}
