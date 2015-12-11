//
// Created by VodalokLab on 2015/12/10.
//

#ifndef HW2_ADDCOMMAND_H
#define HW2_ADDCOMMAND_H

#include "Command.h"

class AddCircleCommand : public Command{
public:
    AddCircleCommand();

    virtual void Execute(GraphicsModel *model);

    virtual void Unexecute(GraphicsModel *model);
private:
    Graphics* _addedGraphics;
};


#endif //HW2_ADDCOMMAND_H
