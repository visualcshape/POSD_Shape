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
    //TODO :Fix Bug : Find the composite
    if(_graphicsToGroup.size() == 0)
        _graphicsToGroup = *model->getSelectedGraphics();
    else {
        //Find and update...
        for (vector<Graphics *>::iterator iterator = _graphicsToGroup.begin();
             iterator != _graphicsToGroup.end(); iterator++) {
            CompositeGraphics *converted = dynamic_cast<CompositeGraphics *>(*iterator);
            if (!converted)
                continue;
            vector<Graphics *> *modelContent = model->getGraphicsVector();
            for (vector<Graphics *>::iterator modelIterator = modelContent->begin();
                 modelIterator != modelContent->end(); modelIterator++) {
                CompositeGraphics *modelCompositeGraphics = dynamic_cast<CompositeGraphics *>(*modelIterator);
                if (!modelCompositeGraphics)
                    continue;
                //if same, replace it.
                if (modelCompositeGraphics->isSameGraphic((*converted->getContent())[0])) {
                    int index = iterator - _graphicsToGroup.begin();
                    _graphicsToGroup[index] = modelCompositeGraphics;
                    break;
                }
            }
        }
    }

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
