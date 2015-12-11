//
// Created by VodalokLab on 2015/12/4.
//

#ifndef HW2_COMMAND_H
#define HW2_COMMAND_H

#include "GraphicsModel.h"

class Command{
public:
    virtual ~Command() {}

    virtual void Execute(GraphicsModel *model) = 0;

    virtual void Unexecute(GraphicsModel* model) = 0;

protected:
    Command() {}
};

#endif //HW2_COMMAND_H
