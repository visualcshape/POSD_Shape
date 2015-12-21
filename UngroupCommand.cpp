//
// Created by VodalokLab on 2015/12/10.
//

#include "UngroupCommand.h"
#include <qdebug.h>
#include "CompositeGraphics.h"

UngroupCommand::UngroupCommand() {
    _graphicToUngroup = NULL;
}

void UngroupCommand::Execute(GraphicsModel *model) {
    //
    bool isFind = false;
    if(!_graphicToUngroup)
        _graphicToUngroup = (*model->getSelectedGraphics())[0];
    else{
        //Find Composite Graphics...
        vector<Graphics*>* graphics = model->getGraphicsVector();
        for(vector<Graphics*>::iterator iterator = graphics->begin() ; iterator != graphics->end(),!isFind ; iterator++){
            CompositeGraphics* compositeGraphics = dynamic_cast<CompositeGraphics*>((*iterator));
            if(!compositeGraphics)
                continue;
            vector<Graphics*>* compositeContent = compositeGraphics->getContent();
            for(vector<Graphics*>::iterator findIterator = compositeContent->begin() ; findIterator != compositeContent->end() ; findIterator++){
                if(*findIterator == _ungropupedGraphics[0]){
                    _graphicToUngroup = compositeGraphics;
                    isFind = true;
                    break;
                }
            }
        }
    }

    _ungropupedGraphics = *model->ungroupGraphic(_graphicToUngroup);
    model->cleanUpHitGraphics();
    qDebug() << "Ungroup executed";
}

void UngroupCommand::Unexecute(GraphicsModel *model) {
    //TODO:Bug fix Ungroup update composite graphic.
    _graphicToUngroup = model->groupGraphics(&_ungropupedGraphics);
    qDebug() << "Ungroup unexecuted";
}
