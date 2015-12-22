//
// Created by VodalokLab on 2015/12/21.
//

#include "MoveUpCommand.h"

void MoveUpCommand::Execute(GraphicsModel *model) {
    if(!_graphicBeMoved) {
        _compositeGraphics = model->getFocusedCompositeGraphic();
        _graphicBeMoved = model->getGraphicBeFocus();
    }
    model->moveGraphicUpInVector(_compositeGraphics->getContent(), _graphicBeMoved);
}

void MoveUpCommand::Unexecute(GraphicsModel *model) {
    model->moveGraphicDownInVector(_compositeGraphics->getContent(),_graphicBeMoved);
}

MoveUpCommand::MoveUpCommand() {
    _graphicBeMoved = NULL;
    _compositeGraphics = NULL;
}
