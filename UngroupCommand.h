//
// Created by VodalokLab on 2015/12/10.
//

#ifndef HW2_UNGROUPCOMMAND_H
#define HW2_UNGROUPCOMMAND_H

#include "Command.h"
#include "Graphics.h"
#include <vector>

using namespace std;

class UngroupCommand : public Command {
private:
    vector<Graphics*> _ungropupedGraphics;
    Graphics* _graphicToUngroup;
public:
    UngroupCommand();

    virtual void Execute(GraphicsModel *model);

    virtual void Unexecute(GraphicsModel *model);
};


#endif //HW2_UNGROUPCOMMAND_H
