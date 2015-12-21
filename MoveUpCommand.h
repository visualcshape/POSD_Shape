//
// Created by VodalokLab on 2015/12/21.
//

#ifndef HW2_MOVEUPCOMMAND_H
#define HW2_MOVEUPCOMMAND_H

#include "Command.h"

class MoveUpCommand : public Command{
private:

public:
    MoveUpCommand();

    virtual void Execute(GraphicsModel *model);

    virtual void Unexecute(GraphicsModel *model);
};


#endif //HW2_MOVEUPCOMMAND_H
