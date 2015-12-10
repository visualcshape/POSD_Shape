//
// Created by VodalokLab on 2015/12/10.
//

#ifndef HW2_COMMANDMANAGER_H
#define HW2_COMMANDMANAGER_H

#include <stack>
#include "Command.h"
#include "GraphicsModel.h"
#include "PresentationModel.h"

using namespace std;

class CommandManager {
private:
    static CommandManager* _instance;

    GraphicsModel* _graphicsModel;
    PresentationModel* _presentationModel;
    stack<Command*> _executedCommands;
    stack<Command*> _unexecutedCommands;

    void CheckUndoRedoButtonCanEnabled();
protected:
    CommandManager();
public:
    static CommandManager* instance();

    void setGraphicsModel(GraphicsModel* model);
    void setPresentationModel(PresentationModel *presentationModel);
    void Undo();
    void Execute(Command* command);
    void Redo();
};


#endif //HW2_COMMANDMANAGER_H

