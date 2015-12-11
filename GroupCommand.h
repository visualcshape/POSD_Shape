//
// Created by VodalokLab on 2015/12/10.
//

#ifndef HW2_GROUPCOMMAND_H
#define HW2_GROUPCOMMAND_H

#include "Command.h"
#include "Graphics.h"
#include <vector>

using namespace std;

class GroupCommand : public Command {
private:
    Graphics* _groupedGraphic;
    vector<Graphics*> _graphicsToGroup;
public:
    GroupCommand();

    virtual void Execute(GraphicsModel *model);

    virtual void Unexecute(GraphicsModel *model);
};


#endif //HW2_GROUPCOMMAND_H
