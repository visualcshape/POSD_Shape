//
// Created by VodalokLab on 2015/12/4.
//

#ifndef HW2_GRAPHICSMODEL_H
#define HW2_GRAPHICSMODEL_H
#include "Graphics.h"
#include <vector>
#include "Subject.h"
#include "SetAllGraphicsFocusToFalseVisitor.h"
#include "CompositeGraphics.h"

using namespace std;

class GraphicsModel : public Subject {
public:
    GraphicsModel(){
        _graphicsVector = new vector<Graphics*>();
        _selectedGraphics = new vector<Graphics*>();
        _focusedCompositeGraphic = NULL;
        _graphicBeFocus = NULL;
    }

    void setGraphicsVector(vector<Graphics*>* graphicVector);

    Graphics * addRectangleOnOriginalPoint();

    Graphics * addCircleOnOriginalPoint();

    Graphics * addSquareOnOriginalPoint();

    void pushBackGraphic(Graphics* graphicToPush);

    void insertGraphicFromFront(Graphics* graphicToInsert);

    void translationSelectedGraphics(QPoint translationLength);

    //Return Grouped Graphics...
    Graphics * groupGraphics(vector<Graphics *> *graphicsToGroup);

    vector<Graphics*>* ungroupGraphic(Graphics* compositeGraphicToUngroup);

    void deleteGraphic(Graphics *graphicToDelete, bool deletePointer);

    bool saveFile(const char* fileName);

    bool loadFile(const char* fileName);

    void addToSelectedGraphicsIfHit(QPointF pressPoint);

    void cleanUpHitGraphics();

    bool isHitSelectedGraphicBoundingBox(QPointF pressPoint);

    vector<Graphics*>* getSelectedGraphics();

    vector<Graphics*>* getGraphicsVector(){ return _graphicsVector;}

    void describeModel();

    CompositeGraphics* hitCompositeGraphic(vector<Graphics*>* domain,QPointF point);

    CompositeGraphics* hitCompositeGraphic(CompositeGraphics* domain,QPointF point);

    Graphics *hitGraphicInGraphicVector(vector<Graphics *> *graphicVector, QPointF position);

    CompositeGraphics* getFocusedCompositeGraphic();

    void changeFocusGraphic(CompositeGraphics *changeToGraphic);

    bool IsPointInGraphicBoundingBox(Graphics* graphics, QPointF point);

    void setGraphicBeFocused(Graphics* graphicsToSet,bool focused);

    Graphics* getGraphicBeFocus();

    void cleanGraphicBeFocus();

    void moveGraphicUpInVector(vector<Graphics*>* content,Graphics* moveGraphic);

    void moveGraphicDownInVector(vector<Graphics*>* content,Graphics* moveIndex);

    CompositeGraphics* updateGraphics(CompositeGraphics* graphicsToUpdate);
private:
    vector<Graphics*>* _graphicsVector;

    vector<Graphics*>* _selectedGraphics;

    CompositeGraphics* _focusedCompositeGraphic;

    Graphics* _graphicBeFocus;

    CompositeGraphics *findCompositeInGraphics(CompositeGraphics *compositeGraphics, Graphics *sample);
};


#endif //HW2_GRAPHICSMODEL_H
