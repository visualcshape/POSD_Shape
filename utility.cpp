//
// Created by Vodalok on 2015/11/2.
//

#include "Utility.h"
#include <fstream>

using namespace std;

void Utility::deleteSpace(string &stringToDeleteSpace) {
    while(stringToDeleteSpace[0]==' ')
        stringToDeleteSpace.erase(0,1);
}

void Utility::checkFileExist(const char* fileName) {
    fstream fileStream;
    string EXCEPTION = "File does not exist.";

    fileStream.open(fileName);
    if (!fileStream.is_open())
        throw string(EXCEPTION);
    fileStream.close();
}
