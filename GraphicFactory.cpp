//
// Created by VodalokLab on 2015/10/29.
//

#include "GraphicFactory.h"
#include <fstream>
#include <sstream>
#include "CompositeGraphicFactory.h"
#include "SimpleGraphicFactory.h"
#include <stdlib.h>
#include "DescriptionVisitor.h"
#include "Utility.h"

using std::fstream;
using std::stringstream;

Graphics *GraphicsFactory::buildGraphicsFromFile(const char *fileName) {
    Utility::checkFileExist(fileName);

    string content = this->fileContentAsString(fileName);
    processContent(content);

    _isFinal = true;
    compose();

    return _compGraphicsStack.top().second;
}

void GraphicsFactory::processContent(string &content) {
    stringstream contentStreamString(content);
    string line;

    while (getline(contentStreamString, line)) {
        const char *aLine = line.c_str();
        _curLevel = 0;
        countLevel(aLine, _curLevel);
        Graphics *producedGraphic = this->extractGraphicsFromOneLine(line, _curLevel);
        if (!_compGraphicsStack.empty()) {
            if (_curLevel < _compGraphicsStack.top().first) {
                compose();
            }
        }

        _compGraphicsStack.push(std::make_pair(_curLevel, producedGraphic));
        takeSnapShot();
    }
}

void GraphicsFactory::countLevel(const char *aLine, int &level) const {//Count level
    while (*aLine == ' ') {
        level++;
        //Jump 2 * Space
        aLine++;
        aLine++;
    }
    return;
}

string GraphicsFactory::fileContentAsString(const char *fileName) {
    fstream fileStream;
    stringstream buffer;
    fileStream.open(fileName, std::ios::in);
    string content = "";

    buffer << fileStream.rdbuf();

    content = buffer.str();

    return content;
}

Graphics *GraphicsFactory::extractGraphicsFromOneLine(string &contents, int &level) {
    stringstream graphicStringStream;
    string graphicString;
    CompositeGraphicFactory *compositeGraphicFactory = new CompositeGraphicFactory();
    SimpleGraphicFactory *simpleGraphicFactory = new SimpleGraphicFactory();
    Graphics *ret = 0;

    graphicStringStream << contents;
    graphicStringStream >> graphicString;

    if (graphicString == "Comp")
        ret = compositeGraphicFactory->createGraphic(contents);
    else
        ret = simpleGraphicFactory->createGraphic(contents);

    delete simpleGraphicFactory;
    delete compositeGraphicFactory;
    return ret;
}

void GraphicsFactory::compose() {
    stack<Graphics *> graphicPendToComposedStack;

    if (!_isFinal) {
        while (!(_curLevel == _compGraphicsStack.top().first)) {
            Graphics *popped = _compGraphicsStack.top().second;
            _compGraphicsStack.pop();
            graphicPendToComposedStack.push(popped);
        }
    } else {
        while (_compGraphicsStack.top().first != 0) {
            Graphics *popped = _compGraphicsStack.top().second;
            _compGraphicsStack.pop();
            graphicPendToComposedStack.push(popped);
        }
    }

    Graphics *compositeGraphic = _compGraphicsStack.top().second;
    while (!graphicPendToComposedStack.empty()) {
        compositeGraphic->add(graphicPendToComposedStack.top());
        graphicPendToComposedStack.pop();
    }
    takeSnapShot();
}

string GraphicsFactory::getSnapShotByLine(const int line) {
    return _snapShot[line - 1];
}

void GraphicsFactory::takeSnapShot() {
    const char COMP_NOT_CONTAIN_SIMPLE_GRAPHICS[] = "Comp R(0,0,0,0)\n";
    stack<pair<int, Graphics *> > reversedStack;
    string snapshot = "";
    int poppedLevel = 0;
    Graphics *poppedGraphics = 0;
    while (!_compGraphicsStack.empty()) {
        reversedStack.push(std::make_pair(_compGraphicsStack.top().first, _compGraphicsStack.top().second));
        _compGraphicsStack.pop();
    }
    while (!reversedStack.empty()) {
        poppedLevel = reversedStack.top().first;
        poppedGraphics = reversedStack.top().second;
        char levelBuff[100];
        itoa(poppedLevel, levelBuff, 10);
        snapshot += levelBuff;
        snapshot += ", ";
        if (poppedGraphics->getDescription() == COMP_NOT_CONTAIN_SIMPLE_GRAPHICS) {
            snapshot += "Comp";
        } else {
            string des = poppedGraphics->getDescription();
            if (des.find("Comp") != string::npos) {
                //Expand tree
                DescriptionVisitor descriptionVisitor;
                string processed = "";
                poppedGraphics->accept(descriptionVisitor);
                string compDescription = descriptionVisitor.getDescription();
                stringstream compDescriptionStringStream(compDescription);
                string line;
                int previousLevel = 0;
                while (std::getline(compDescriptionStringStream, line)) {
                    if (line.find("Comp R") != std::string::npos) {
                        //delete space
                        Utility::deleteSpace(line);
                        processed += line;
                        processed += '[';
                        continue;
                    }
                    int nowLevel = 0;
                    countLevel(line.c_str(),nowLevel);
                    if(nowLevel < previousLevel) {
                        processed.erase(processed.length() - 2, 2);
                        processed += "], ";
                    }
                    previousLevel = nowLevel;
                    replaceSimpleNameToFullName(line);
                    processed += line;
                    processed += ", ";
                }
                //delete last comma
                processed.erase(processed.length() - 2, 2);
                processed += ']';
                des = processed;
            }
            //delete last index '\n'
            if (des[des.length() - 1] == '\n')
                des.erase(des.length() - 1, 1);
            replaceSimpleNameToFullName(des);
            snapshot += des;
        }
        _compGraphicsStack.push(std::make_pair(poppedLevel, poppedGraphics));
        reversedStack.pop();
        snapshot += '\n';
    }
    _snapShot.push_back(snapshot);
}

void GraphicsFactory::replaceSimpleNameToFullName(string &des) const {
    Utility::deleteSpace(des);
    switch (des[0]) {
        case 'S':
            des.replace(0, 1, "Square");
            break;
        case 'C':
            if (des[1] != 'o')
                des.replace(0, 1, "Circle");
            break;
        case 'R':
            des.replace(0, 1, "Rectangle");
            break;
    }
}

vector<Graphics *>* GraphicsFactory::buildMultiRootGraphicsFromFile(const char *fileName) {
    vector<Graphics*>* _returnVector = new vector<Graphics*>();

    Utility::checkFileExist(fileName);
    this->buildGraphicsFromFile(fileName);

    while(!_compGraphicsStack.empty()){
        _returnVector->push_back(_compGraphicsStack.top().second);
        _compGraphicsStack.pop();
    }

    return  _returnVector;
}

string GraphicsFactory::getLastSnapShot() {
    return _snapShot[_snapShot.size()-1];
}
