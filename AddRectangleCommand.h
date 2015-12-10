//
// Created by VodalokLab on 2015/12/10.
//

#ifndef HW2_ADDRECTANGLECOMMAND_H
#define HW2_ADDRECTANGLECOMMAND_H

#include "Command.h"

class AddRectangleCommand : public Command{
private:
    Graphics* _addedGraphic;
public:
    AddRectangleCommand();

    virtual void Execute(GraphicsModel *model);

    virtual void Unexecute(GraphicsModel *model);
};


#endif //HW2_ADDRECTANGLECOMMAND_H
