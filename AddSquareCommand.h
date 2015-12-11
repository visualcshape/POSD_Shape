//
// Created by VodalokLab on 2015/12/10.
//

#ifndef HW2_ADDSQUARECOMMAND_H
#define HW2_ADDSQUARECOMMAND_H

#include "Command.h"
#include "Graphics.h"

class AddSquareCommand : public Command{
public:
    Graphics* _addedGraphics;
public:
    AddSquareCommand();

    virtual void Execute(GraphicsModel *model);

    virtual void Unexecute(GraphicsModel *model);
};


#endif //HW2_ADDSQUARECOMMAND_H
