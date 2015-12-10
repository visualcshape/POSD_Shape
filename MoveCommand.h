//
// Created by VodalokLab on 2015/12/10.
//

#ifndef HW2_MOVECOMMAND_H
#define HW2_MOVECOMMAND_H

#include "Command.h"
#include <QPointF>
#include <vector>

using namespace std;

class MoveCommand : public Command {
private:
    vector<QPointF> _beforeMove;
    vector<QPointF> _afterMoved;
    vector<Graphics*> _movedGraphics;
public:
    MoveCommand();

    virtual void Execute(GraphicsModel *model);

    virtual void Unexecute(GraphicsModel *model);

    void ExecuteStart(GraphicsModel* model);

    void ExecuteEnd(GraphicsModel* model);
};


#endif //HW2_MOVECOMMAND_H
