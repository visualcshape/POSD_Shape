#ifndef _SIMPLE_GRAPHIC_H_
#define _SIMPLE_GRAPHIC_H_

#include "Graphics.h"
#include "shape.h"

class SimpleGraphics :public Graphics{
private:
	Shape* _shape;
public:
	SimpleGraphics();

	SimpleGraphics(Shape* shape);

	void accept(GraphicsVisitor &graphicVisitor);

    double calculateArea();

	virtual string getDescription();

	string getDescription(int level);

	void increaseCompositeLevel();

	virtual void draw(QGraphicsScene* scene);

	virtual void translation(QPoint translationLength);


	virtual void setPosition(QPoint position);

	virtual QPoint getPosition();
};

#endif