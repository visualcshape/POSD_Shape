//
// Created by VodalokLab on 2015/10/16.
//

#ifndef HW2_DESCRIPTION_VISITOR_H
#define HW2_DESCRIPTION_VISITOR_H

#include "GraphicsVisitor.h"
#include "Graphics.h"
#include <string>
#include <vector>
#include <stack>

using std::vector;
using std::stack;
using std::string;

class DescriptionVisitor : public GraphicsVisitor{
private:
    std::string _desc;
public:
    DescriptionVisitor():_desc(""){};

    void visitCompositeGraphic(Graphics* graphics);

    void visitSimpleGraphic(Graphics* graphics);

    std::string getDescription();
};


#endif //HW2_DESCRIPTIONVISITOR_H
