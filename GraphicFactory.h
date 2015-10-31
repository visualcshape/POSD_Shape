//
// Created by VodalokLab on 2015/10/29.
//

#ifndef HW2_GRAPHICFACTORY_H
#define HW2_GRAPHICFACTORY_H

#include "Graphics.h"
#include <string>
#include <stack>
#include <utility>

using std::string;
using std::stack;
using std::pair;

class GraphicsFactory {
private:
    string _contentString;
    int _curLevel;
    stack<pair<int,Graphics*> > _compGraphicsStack;
    bool _isFinal;

    void countLevel(const char *aLine, int &level) const;
public:
    GraphicsFactory() {
        _contentString = "";
        _curLevel = 0;
        _isFinal = false;
    }

    Graphics* buildGraphicsFromFile(const char* fileName);

    string fileContentAsString(const char* fileName);

    Graphics *extractGraphicsFromOneLine(string &contents, int &level);

    virtual Graphics* createGraphic(string &content) {return new Graphics();}

    void compose();;
};

#endif //HW2_GRAPHICFACTORY_H
