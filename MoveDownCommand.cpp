//
// Created by VodalokLab on 2015/12/21.
//

#include "MoveDownCommand.h"

void MoveDownCommand::Execute(GraphicsModel *model) {
    if(!_graphicBeMoved) {
        _compositeGraphics = model->getFocusedCompositeGraphic();
        _graphicBeMoved = model->getGraphicBeFocus();
    }
    model->moveGraphicDownInVector(_compositeGraphics->getContent(),_graphicBeMoved);
}

void MoveDownCommand::Unexecute(GraphicsModel *model) {
    model->moveGraphicUpInVector(_compositeGraphics->getContent(),_graphicBeMoved);
}

MoveDownCommand::MoveDownCommand() {
    _compositeGraphics = NULL;
    _graphicBeMoved = NULL;
}
