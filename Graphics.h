#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_
#include <string>
#include "BoundingBox.h"
#include "GraphicsVisitor.h"
#include <QGraphicsScene>

using std::string;

class Graphics{
protected:
	BoundingBox _boundingBox;
	int _compositeLevel;
	bool _selected;
public:
	Graphics():_boundingBox(0,0,0,0),_compositeLevel(0),_selected(false){}

	virtual BoundingBox getBoundingBox(){ return _boundingBox; }
	
	virtual void add(Graphics* graphic){ throw std::string("Cannot add child"); }

	virtual void accept(GraphicsVisitor &graphicVisitor) {};

	virtual double calculateArea(){return 0.;}

	virtual  string getDescription() {return "";}

	virtual string getDescription(int level){return "";}

	virtual  int getCompositeLevel(){return _compositeLevel;}

	virtual void increaseCompositeLevel() {_compositeLevel++;}

	virtual void decreaseCompositeLevel() {_compositeLevel--;}

	virtual void draw(QGraphicsScene* scene){}

    virtual void setSelected(bool selected){_selected = selected;}

    inline bool isSelected(){return _selected;}

    virtual void translation(QPoint translationLength){}

	virtual void setPosition(QPoint position){}

	virtual QPoint getPosition(){}
};

#endif