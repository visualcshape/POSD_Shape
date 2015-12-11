//
// Created by VodalokLab on 2015/12/10.
//

#ifndef HW2_DELETECOMMAND_H
#define HW2_DELETECOMMAND_H

#include "Command.h"
#include "Graphics.h"

class DeleteCommand : public Command{
public:
    Graphics* _deleteGraphic;
public:
    DeleteCommand();

    virtual void Execute(GraphicsModel *model);

    virtual void Unexecute(GraphicsModel *model);
};


#endif //HW2_DELETECOMMAND_H
