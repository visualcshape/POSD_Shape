//
// Created by VodalokLab on 2015/10/29.
//

#include "GraphicFactory.h"
#include <fstream>
#include <sstream>
#include "CompositeGraphicFactory.h"
#include "SimpleGraphicFactory.h"

using std::fstream;
using std::stringstream;

Graphics *GraphicsFactory::buildGraphicsFromFile(const char *fileName) {
    fstream fileStream;
    string EXCEPTION = "File does not exist.";

    fileStream.open(fileName);
    if (!fileStream.is_open())
        throw string(EXCEPTION);
    fileStream.close();

    string content = this->fileContentAsString(fileName);
    processContent(content);

    _isFinal = true;
    compose();

    return _compGraphicsStack.top().second;
}

void GraphicsFactory::processContent(string& content) {
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
}

string GraphicsFactory::getSnapShotByLine(const int line) {
    return _snapShot[line-1];
}

void GraphicsFactory::takeSnapShot() {
    const char COMP_NOT_CONTAIN_SIMPLE_GRAPHICS[] = "Comp R(0,0,0,0)\n";
    stack<pair<int,Graphics*> > reversedStack;
    string snapshot;
    int poppedLevel = 0;
    Graphics* poppedGraphics = 0;
    while(!_compGraphicsStack.empty()){
        reversedStack.push(std::make_pair(_compGraphicsStack.top().first,_compGraphicsStack.top().second));
        _compGraphicsStack.pop();
    }
    while(!reversedStack.empty()){
        poppedLevel = reversedStack.top().first;
        poppedGraphics = reversedStack.top().second;
        snapshot += poppedLevel;
        if(poppedGraphics->getDescription()==COMP_NOT_CONTAIN_SIMPLE_GRAPHICS){
            snapshot += ", Comp";
        }else{
            string des = poppedGraphics->getDescription();
            //delete last index '\n'
            des.erase(des.length()-1,1);
            snapshot += des;
        }
        _compGraphicsStack.push(std::make_pair(poppedLevel,poppedGraphics));
        reversedStack.pop();
        snapshot+='\n';
    }
    _snapShot.push_back(snapshot);
}
