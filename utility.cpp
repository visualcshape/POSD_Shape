//
// Created by Vodalok on 2015/11/2.
//

#include "Utility.h"

void Utility::deleteSpace(string &stringToDeleteSpace) {
    while(stringToDeleteSpace[0]==' ')
        stringToDeleteSpace.erase(0,1);
}
