//
// Created by VodalokLab on 2015/12/4.
//

#ifndef HW2_GRAPHICSMODEL_H
#define HW2_GRAPHICSMODEL_H
#include "Graphics.h"
#include <vector>
#include "Subject.h"

using namespace std;

class GraphicsModel : public Subject {
public:
    GraphicsModel(){
        _graphicsVector = 0;
    }

    void setGraphicsVector(vector<Graphics*>* graphicVector) {
        _graphicsVector = graphicVector;
        Notify();
    }

    vector<Graphics*>* getGraphicsVector(){ return _graphicsVector;}
private:
    vector<Graphics*>*_graphicsVector;
};


#endif //HW2_GRAPHICSMODEL_H
