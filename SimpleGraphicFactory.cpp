//
// Created by VodalokLab on 2015/10/29.
//

#include "SimpleGraphicFactory.h"
#include "SimpleGraphics.h"
#include <sstream>
#include <stdlib.h>
#include "Utility.h"

using std::stringstream;

Graphics *SimpleGraphicFactory::createGraphic(string &content) {
    string graphicType = "";
    string graphicAttribute = "";
    string token = "";
    SimpleGraphics* ret = 0;
    const char DELIM = '(';
    stringstream tokenStringStream(content);
    std::getline(tokenStringStream, token, DELIM);
    graphicType = token;
    Utility::deleteSpace(graphicType);
    std::getline(tokenStringStream,token, DELIM);

    //remove right brace
    token.erase(token.length()-1,1);
    graphicAttribute = token;

    switch(graphicType[0]){
        case 'R':{
            Rectangle* pRectangle = createRectangle(graphicAttribute);
            ret = new SimpleGraphics(pRectangle);
        }
            break;
        case 'C':{
            Circle* circle = createCircle(graphicAttribute);
            ret = new SimpleGraphics(circle);
        }
        break;
        case 'S':{
            Square* square = createSquare(graphicAttribute);
            ret = new SimpleGraphics(square);
        }
        break;
    }

    return ret;
}

Rectangle *SimpleGraphicFactory::createRectangle(string &graphicAttribute){
    int x;
    int y;
    int length;
    int width;
    string token;
    const char DELIM = ',';
    string streamable = graphicAttribute;
    stringstream graphicAttributeStream(streamable);
    
    std::getline(graphicAttributeStream,token,DELIM);
    x = atoi(token.c_str());
    std::getline(graphicAttributeStream,token,DELIM);
    y = atoi(token.c_str());
    std::getline(graphicAttributeStream,token,DELIM);
    length = atoi(token.c_str());
    std::getline(graphicAttributeStream,token,DELIM);
    width = atoi(token.c_str());
    return  new Rectangle(x,y,length,width);
}

Square *SimpleGraphicFactory::createSquare(string &graphicAttribute) {
    string token = "";
    const char DELIM = ',';
    int x,y,length;
    string streamable = graphicAttribute;
    stringstream graphicAttributeStream(streamable);
    
    std::getline(graphicAttributeStream,token,DELIM);
    x = atoi(token.c_str());
    std::getline(graphicAttributeStream,token,DELIM);
    y = atoi(token.c_str());
    std::getline(graphicAttributeStream,token,DELIM);
    length  = atoi(token.c_str());
    return  new Square(x,y,length);
}

Circle *SimpleGraphicFactory::createCircle(string &graphicAttribute) {
    int circleCenterX,circleCenterY,radius;
    string token = "";
    const char DELIM = ',';
    string streamable = graphicAttribute;
    stringstream graphicAttributeStream(streamable);
    
    std::getline(graphicAttributeStream,token,DELIM);
    circleCenterX = atoi(token.c_str());
    std::getline(graphicAttributeStream,token,DELIM);
    circleCenterY = atoi(token.c_str());
    std::getline(graphicAttributeStream,token,DELIM);
    radius = atoi(token.c_str());
    return  new Circle(circleCenterX,circleCenterY,radius);
}
