//
// Created by Vodalok on 2015/11/2.
//

#ifndef HW2_UTILITY_H
#define HW2_UTILITY_H

#include <string>
#include <vector>

using std::vector;
using std::string;

class Utility {
public:
    static void deleteSpace(string &stringToDeleteSpace);
    static void checkFileExist(const char* fileName);
};


#endif //HW2_UTILITY_H
