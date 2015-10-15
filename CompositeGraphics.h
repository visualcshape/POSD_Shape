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
};

#endif