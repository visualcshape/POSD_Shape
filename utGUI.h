//
// Created by VodalokLab on 2015/11/25.
//

#ifndef HW2_UTGUI_H
#define HW2_UTGUI_H

#include "GUI.h"
#include <QApplication>
#include "cppunitlite/TestHarness.h"

int argc = 0;
char a[2] = {'0','1'};
char* argv[1] = {a};

TEST (GUITest, GUI){
    QApplication application(argc,argv);
    GUI gui;
    gui.show();
    application.exec();
}

#endif //HW2_UTGUI_H
