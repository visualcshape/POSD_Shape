//
// Created by VodalokLab on 2015/10/29.
//

#ifndef HW2_GRAPHICFACTORY_H
#define HW2_GRAPHICFACTORY_H

#include "Graphics.h"
#include <string>
#include <stack>

using std::string;
using std::stack;

class GraphicsFactory {
private:
    string _contentString;
    stack<Graphics> _compGraphicsStack;

    void countLevel(const char *aLine, int &level) const;
public:
    GraphicsFactory() {
        _contentString = "";
    }

    Graphics* buildGraphicsFromFile(const char* fileName);

    string fileContentAsString(const char* fileName);

    Graphics *extractGraphicsFromOneLine(string &contents, int &level);

    void compose();;
};

#endif //HW2_GRAPHICFACTORY_H
