//
// Created by VodalokLab on 2015/10/29.
//

#ifndef HW2_GRAPHICFACTORY_H
#define HW2_GRAPHICFACTORY_H

#include "Graphics.h"
#include <string>

using std::string;

class GraphicsFactory {
public:
    GraphicsFactory() { }

    Graphics* buildGraphicsFromFile(const char* fileName);
    string fileContentAsString(const char* fileName);
    Graphics* extractGraphicsFromOneLine(string& contents);
    void compose();
};

#endif //HW2_GRAPHICFACTORY_H
