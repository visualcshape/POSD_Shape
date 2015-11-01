//
// Created by VodalokLab on 2015/10/30.
//

#ifndef HW2_UTHW3_H
#define HW2_UTHW3_H

#include "GraphicFactory.h"
#include "cppunitlite/TestHarness.h"
#include <stack>
#include <utility>

using std::stack;
using std::pair;
using std::make_pair;

TEST (buildGraphicsFromFileExceptionTest, GraphicsFactory){
    string WRONG_FILE_NAME = "arbitaryFile.txt";
    GraphicsFactory graphicsFactory;
    try{
        graphicsFactory.buildGraphicsFromFile(WRONG_FILE_NAME.c_str());
    }catch (string exception){
        string EXPECT = "File does not exist.";
        CHECK(EXPECT == exception);
    }
}

TEST(buildGraphicsFromFileTest, GraphicsFactory){
    const char FILE_NAME[] = "f1.txt";
    string EXPECT;
    GraphicsFactory factory;
    EXPECT = "Comp R(-2,-2,3,4)\n"
            "  Comp R(-2,-2,3,3)\n"
            "    C(0,0,1)\n"
            "    S(-2,-2,2)\n"
            "  R(-1,-1,1,3)\n";
    DescriptionVisitor descriptionVisitor;
    Graphics* builtGraphic = factory.buildGraphicsFromFile(FILE_NAME);
    builtGraphic->accept(descriptionVisitor);
    CHECK(EXPECT==descriptionVisitor.getDescription());
}

TEST (fileContentsAsStringfileTest, GraphicsFactory) {
    string FILE_NAME = "f1.txt";
    string EXPECT;
    EXPECT = "Comp R(-2,-2,3,4)\n"
            "  Comp R(-2,-2,3,3)\n"
            "    C(0,0,1)\n"
            "    S(-2,-2,2)\n"
            "  R(-1,-1,1,3)";
    GraphicsFactory graphicsFactory;
    CHECK(EXPECT == graphicsFactory.fileContentAsString(FILE_NAME.c_str()));
}

TEST(extractGraphicsFromOneLineSimpleGraphicsCircle,GraphicsFactory){
    const char CIRCLE_LINE[] = "C(1,2,2)\n";
    int level = 0;

    GraphicsFactory factory;
    string circleString = CIRCLE_LINE;
    Graphics* extracted = factory.extractGraphicsFromOneLine(circleString,level);
    CHECK(extracted->getDescription()==CIRCLE_LINE);


}

TEST(extractGraphicsFromOneLineSimpleGraphicsSqure,GraphicsFactory){
    const char SQUARE_LINE[] = "S(2,2,2)\n";
    int level = 0;
    GraphicsFactory factory;
    string squareString = SQUARE_LINE;
    Graphics* extracted = factory.extractGraphicsFromOneLine(squareString,level);
    string des = extracted->getDescription();
    CHECK(extracted->getDescription()==SQUARE_LINE);
}

TEST(extractGraphicsFromOneLineCompositeGraphics,GraphicsFactory){
    const char COMP_LINE[] = "Comp R(0,0,0,0)";
    int level = 0;

    string compString = COMP_LINE;
    GraphicsFactory factory;
    Graphics* extracted = factory.extractGraphicsFromOneLine(compString,level);
    CHECK(extracted->getDescription() == COMP_LINE);
}

TEST(composeLine5Test,GraphicsFactory){
    stack<pair<int,Graphics*>> expectStack;
    expectStack.push(make_pair(0,new CompositeGraphics));
    expectStack.push(make_pair(1,new CompositeGraphics));
    expectStack.push(make_pair(2,new SimpleGraphics(new Circle(0,0,1))));
    expectStack.push(make_pair(2,new SimpleGraphics(new Square(-2,-2,2))));


}

TEST(SelfTest,selfTest){
    string FILE_NAME = "f1.txt";
    GraphicsFactory graphicsFactory;
    Graphics* built = graphicsFactory.buildGraphicsFromFile(FILE_NAME.c_str());
    DescriptionVisitor descriptionVisitor;
    built->accept(descriptionVisitor);
    cout << descriptionVisitor.getDescription();
}

#endif //HW2_UTHW3_H
