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
    QPointF _startPoint;
    QPointF _endPoint;
    bool _firstMove;

    vector<Graphics*> _movedGraphics;
public:
    MoveCommand();

    virtual void Execute(GraphicsModel *model);

    virtual void Unexecute(GraphicsModel *model);

    inline void SetStartPoint(QPointF startPoint){
        _startPoint = startPoint;
    }

    inline void SetEndPoint(QPointF endPoint){
        _endPoint = endPoint;
    }
};


#endif //HW2_MOVECOMMAND_H
