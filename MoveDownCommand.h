//
// Created by VodalokLab on 2015/12/21.
//

#ifndef HW2_MOVEDOWNCOMMAND_H
#define HW2_MOVEDOWNCOMMAND_H

#include "Command.h"

class MoveDownCommand:public Command {
private:
    CompositeGraphics* _compositeGraphics;
    Graphics* _graphicBeMoved;
public:
    virtual void Execute(GraphicsModel *model);

    virtual void Unexecute(GraphicsModel *model);

    MoveDownCommand();
};


#endif //HW2_MOVEDOWNCOMMAND_H
