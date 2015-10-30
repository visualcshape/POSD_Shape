//
// Created by VodalokLab on 2015/10/29.
//

#include "GraphicFactory.h"
#include <fstream>
#include <sstream>

using std::fstream;
using std::stringstream;

Graphics *GraphicsFactory::buildGraphicsFromFile(const char *fileName) {
    fstream fileStream;
    string EXCEPTION = "File does not exist.";

    fileStream.open(fileName);
    if(!fileStream.is_open())
        throw string(EXCEPTION);
    fileStream.close();

    this->fileContentAsString(fileName);
    stringstream contentStreamString(_contentString);
    string line;

    while(contentStreamString >> line){
        const char* aLine = line.c_str();
        int level = 0;
        countLevel(aLine, level);
    }
}

void GraphicsFactory::countLevel(const char *aLine, int &level) const {//Count level
    while(aLine == " "){
            level++;
            //Jump 2 * Space
            aLine++;
            aLine++;
    }
}

string GraphicsFactory::fileContentAsString(const char *fileName) {
    fstream fileStream;
    stringstream buffer;
    fileStream.open(fileName, std::ios::in);

    buffer << fileStream.rdbuf();

    _contentString = buffer.str();

    return _contentString;
}

Graphics *GraphicsFactory::extractGraphicsFromOneLine(string &contents, int &level) {

}

void GraphicsFactory::compose() {

}
