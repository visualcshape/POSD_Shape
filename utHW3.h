//
// Created by VodalokLab on 2015/10/30.
//

#ifndef HW2_UTHW3_H
#define HW2_UTHW3_H

#include "GraphicFactory.h"
#include "cppunitlite/TestHarness.h"

TEST (GraphicsFactory, fileContentsAsString) {
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

TEST(GraphicsFactory, BuildGraphicsFromFile){
    string WRONG_FILE_NAME = "arbitaryFile.txt";
    GraphicsFactory graphicsFactory;
    try{
        graphicsFactory.buildGraphicsFromFile(WRONG_FILE_NAME.c_str());
    }catch (string exception){
        string EXPECT = "File does not exist.";
        CHECK(EXPECT == exception);
    }
}

TEST(GraphicsFactory, countLevel){
    string FILE_NAME = "f1.txt";
    GraphicsFactory graphicsFactory;
    graphicsFactory.buildGraphicsFromFile(FILE_NAME.c_str());
}

#endif //HW2_UTHW3_H
