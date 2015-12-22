//
// Created by VodalokLab on 2015/12/21.
//

#include "MoveUpCommand.h"

void MoveUpCommand::Execute(GraphicsModel *model) {
    if(!_graphicBeMoved) {
        _compositeGraphics = model->getFocusedCompositeGraphic();
        _graphicBeMoved = model->getGraphicBeFocus();
    }

    //Find and Update composite graphic
    _compositeGraphics = model->updateGraphics(_compositeGraphics);
    //Graphic be moved update
    CompositeGraphics* compositeGraphics = dynamic_cast<CompositeGraphics*>(_graphicBeMoved);
    //only composite graphic need to update
    if(compositeGraphics)
        _graphicBeMoved = model->updateGraphics(compositeGraphics);

    model->moveGraphicUpInVector(_compositeGraphics->getContent(), _graphicBeMoved);
}

void MoveUpCommand::Unexecute(GraphicsModel *model) {
    //Find and Update composite graphic
    _compositeGraphics = model->updateGraphics(_compositeGraphics);
    //Graphic be moved update
    CompositeGraphics* compositeGraphics = dynamic_cast<CompositeGraphics*>(_graphicBeMoved);
    //only composite graphic need to update
    if(compositeGraphics)
        _graphicBeMoved = model->updateGraphics(compositeGraphics);

    model->moveGraphicDownInVector(_compositeGraphics->getContent(),_graphicBeMoved);
}

MoveUpCommand::MoveUpCommand() {
    _graphicBeMoved = NULL;
    _compositeGraphics = NULL;
}
