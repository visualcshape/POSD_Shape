//
// Created by VodalokLab on 2015/12/10.
//

#include <crtdbg.h>
#include "CommandManager.h"

CommandManager* CommandManager::_instance = NULL;

CommandManager *CommandManager::instance() {

    if(!_instance){
        _instance = new CommandManager();
    }

    return _instance;
}

void CommandManager::Undo() {
    if(_executedCommands.size() > 0){
        Command* undoCommand = _executedCommands.top();
        undoCommand->Unexecute(_graphicsModel);
        _unexecutedCommands.push(undoCommand);
        _executedCommands.pop();
    }
    CheckUndoRedoButtonCanEnabled();
    _graphicsModel->cleanUpHitGraphics();
}

CommandManager::CommandManager() {

}

void CommandManager::Execute(Command *command) {
    command->Execute(_graphicsModel);
    _executedCommands.push(command);
    //if execute the redo will invalid. Clean up redo stack...
    while(_unexecutedCommands.size() != 0) {
        Command* commandToDelete = _unexecutedCommands.top();
        _unexecutedCommands.pop();
        delete commandToDelete;
    }
    CheckUndoRedoButtonCanEnabled();
}

void CommandManager::Redo() {
    if(_unexecutedCommands.size() != 0){
        Command* redoCommand = _unexecutedCommands.top();
        redoCommand->Execute(_graphicsModel);
        _unexecutedCommands.pop();
        _executedCommands.push(redoCommand);
    }
    CheckUndoRedoButtonCanEnabled();
    _graphicsModel->cleanUpHitGraphics();
}

void CommandManager::setGraphicsModel(GraphicsModel *model) {
    _graphicsModel = model;
}

void CommandManager::setPresentationModel(PresentationModel *presentationModel) {
    _presentationModel = presentationModel;
}

void CommandManager::CheckUndoRedoButtonCanEnabled() {
    if(_executedCommands.size() == 0)
        _presentationModel->SetUndoEnabled(false);
    else
        _presentationModel->SetUndoEnabled(true);

    if(_unexecutedCommands.size() == 0)
        _presentationModel->SetRedoEnabled(false);
    else
        _presentationModel->SetRedoEnabled(true);

}

void CommandManager::CleanUpAllCommand() {
    Command* commandToDelete = NULL;
    while(!this->_executedCommands.empty()) {
         commandToDelete = _executedCommands.top();
        _executedCommands.pop();
        delete commandToDelete;
    }
    while(!this->_unexecutedCommands.empty()) {
        commandToDelete = _unexecutedCommands.top();
        _unexecutedCommands.pop();
        delete commandToDelete;
    }

    CheckUndoRedoButtonCanEnabled();
}
