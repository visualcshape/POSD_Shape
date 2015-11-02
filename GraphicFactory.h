//
// Created by VodalokLab on 2015/10/29.
//

#ifndef HW2_GRAPHICFACTORY_H
#define HW2_GRAPHICFACTORY_H

#include "Graphics.h"
#include <string>
#include <stack>
#include <utility>
#include <vector>

using std::string;
using std::stack;
using std::pair;
using std::vector;

class GraphicsFactory {
private:
    int _curLevel;
    stack<pair<int,Graphics*> > _compGraphicsStack;
    vector<string> _snapShot;
    bool _isFinal;

    void countLevel(const char *aLine, int &level) const;
    void takeSnapShot();
public:
    GraphicsFactory() {
        _curLevel = 0;
        _isFinal = false;
    }

    Graphics* buildGraphicsFromFile(const char* fileName);

    string fileContentAsString(const char* fileName);

    Graphics *extractGraphicsFromOneLine(string &contents, int &level);

    virtual Graphics* createGraphic(string &content) {return new Graphics();}

    void compose();

    void processContent(string& content);

    string getSnapShotByLine(const int line);
};

#endif //HW2_GRAPHICFACTORY_H
