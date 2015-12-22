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
    bool _focused;
public:
	Graphics():_boundingBox(0,0,0,0),_compositeLevel(0),_selected(false),_focused(false){}

	virtual BoundingBox getBoundingBox(){ return _boundingBox; }
	
	virtual void add(Graphics* graphic){ throw std::string("Cannot add child"); }

	virtual void addFromFront(Graphics* graphicsToAdd){throw std::string("Cannot add child");}

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

	virtual void setPosition(QPoint position){
		//convert position to bounding box position
		QPoint diff = position - QPoint(_boundingBox.llx(),_boundingBox.lly());
		this->translation(diff);
	}

	virtual QPoint getPosition(){return QPoint(0,0);}

	virtual bool isSameGraphic(Graphics* graphicsToCompare){return false;}

    virtual void setFocused(bool isFocused){_focused = isFocused;}

    virtual bool isFocused(){return _focused;}
};

#endif