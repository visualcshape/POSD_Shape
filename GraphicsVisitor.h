//
// Created by VodalokLab on 2015/10/15.
//

#ifndef HW2_GRAPHIC_VISITOR_H
#define HW2_GRAPHIC_VISITOR_H

class Graphics;

class GraphicsVisitor {
private:
public:
    virtual void visitCompositeGraphic(Graphics *graphics) = 0;
    virtual void visitSimpleGraphic(Graphics *graphics) = 0;
};


#endif //HW2_GRAPHICVISITOR_H
