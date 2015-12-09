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
        _graphicsVector = new vector<Graphics*>();
        _selectedGraphics = new vector<Graphics*>();
        _selectedGraphic = NULL;
    }

    void setGraphicsVector(vector<Graphics*>* graphicVector);

    void addRectangleOnOriginalPoint();

    void addCircleOnOriginalPoint();

    void addSquareOnOriginalPoint();

    void pushBackGraphic(Graphics* graphicToPush);

    void insertGraphicFromFront(Graphics* graphicToInsert);

    void translationGraphic(Graphics* graphicToTranslate, QPoint translationLength);

    void translationSelectedGraphics(QPoint translationLength);

    void groupGraphics(vector<Graphics*>* graphicsToGroup);

    void ungroupGraphic(Graphics* compositeGraphicToUngroup);

    void deleteGraphic(Graphics *graphicToDelete, bool deletePointer);

    void deleteSelectedGraphics(vector<Graphics*>* graphicsToDelete);

    bool saveFile(const char* fileName);

    bool loadFile(const char* fileName);

    void addToSelectedGraphicsIfHit(QPointF pressPoint);

    void cleanUpHitGraphics();

    bool isHitSelectedGraphicBoundingBox(QPointF pressPoint);

    vector<Graphics*>* getSelectedGraphics();

    //if no graphic hit return null ptr.
    Graphics* hitGraphic(QPointF pressPoint);

    vector<Graphics*>* getGraphicsVector(){ return _graphicsVector;}

    Graphics* getSelectedGraphic();
private:
    vector<Graphics*>* _graphicsVector;

    vector<Graphics*>* _selectedGraphics;

    Graphics* _selectedGraphic;

    bool IsPointInGraphicBoundingBox(Graphics* graphics, QPointF point);

    void changeSelectedGraphic(Graphics* graphic);
};


#endif //HW2_GRAPHICSMODEL_H
