//
// Created by VodalokLab on 2015/12/10.
//

#include "GroupCommand.h"
#include <qdebug.h>
#include "CompositeGraphics.h"

GroupCommand::GroupCommand() {
    _groupedGraphic = NULL;
}

void GroupCommand::Execute(GraphicsModel *model) {
    if(_graphicsToGroup.size() == 0)
        _graphicsToGroup = *model->getSelectedGraphics();
    _groupedGraphic = model->groupGraphics(&_graphicsToGroup);
    model->cleanUpHitGraphics();
    qDebug() << "Group executed";
}

void GroupCommand::Unexecute(GraphicsModel *model) {
    bool isFound = false;
    //Find the composite graphic...
    vector<Graphics*>* graphic = model->getGraphicsVector();
    for(vector<Graphics*>::iterator iterator = graphic->begin() ; iterator != graphic->end(), !isFound ; iterator++){
        CompositeGraphics* compositeGraphics = dynamic_cast<CompositeGraphics*>(*iterator);
        if(compositeGraphics == NULL)
            continue;
        vector<Graphics*> compositeContent = *compositeGraphics->getContent();
        for(vector<Graphics*>::iterator compositeContentIterator = compositeContent.begin() ; compositeContentIterator != compositeContent.end() ; compositeContentIterator++){
            if(_graphicsToGroup[0] == compositeContent[0]) {
                _groupedGraphic = compositeGraphics;
                isFound = true;
                break;
            }
        }
    }
    model->ungroupGraphic(_groupedGraphic);
    qDebug() << "Group unexecuted";
}
