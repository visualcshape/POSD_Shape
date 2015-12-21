#ifndef _COMPOSITE_GRAPHIC_H_
#define _COMPOSITE_GRAPHIC_H_

#include "Graphics.h"
#include "SimpleGraphics.h"
#include <vector>

using std::vector;
using namespace std;

class CompositeGraphics :public Graphics{
private:
	std::vector<Graphics*> _graphics;

	void calculateBoundingBox();
public:
	void add(Graphics* graphic);

	void accept(GraphicsVisitor & visitor);

	double calculateArea();

	string getDescription();

	string getDescription(int level);

	virtual void increaseCompositeLevel();

	virtual void draw(QGraphicsScene* scene);

	virtual void setSelected(bool selected);

    virtual void translation(QPoint translationLength);

    virtual void decreaseCompositeLevel();

    vector<Graphics*>* getContent();

    virtual QPoint getPosition();


    virtual bool isSameGraphic(Graphics *graphicsToCompare);
};

#endif