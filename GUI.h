//
// Created by VodalokLab on 2015/11/25.
//

#ifndef HW2_GUI_H
#define HW2_GUI_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GUI_H
#define GUI_H

#include <QtWidgets/QMainWindow>
#include <Qt>
#include <QGraphicsView>
#include <QtWidgets/QToolBar>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QString>
#include <QWidget>
#include <iostream>
#include <string>
#include <sstream>
#include "Graphics.h"
#include "Observer.h"
#include "GraphicsModel.h"
#include "PresentationModel.h"

using namespace std;


class GUI: public QMainWindow, public Observer
{
Q_OBJECT
public:
    GUI();
    virtual ~GUI();
    void Display();
    void CreateView();
    void CreateActions();
    void CreateMenus();
    void CreateToolButtons();
    void SetActionConnection();
protected:
private:
    QGraphicsView *_graphicsView;
    QGraphicsScene *_scene;
    QWidget *_widget;
    QAction *_aboutDeveloper;
    QAction *_openFile;
    QAction *_saveFile;
    QAction *_drawSquare;
    QAction *_drawRectangle;
    QAction *_drawCircle;
    QAction *_undo;
    QAction *_redo;
    QAction *_group;
    QAction *_ungroup;
    QAction *_deleteGraphic;
    QMenu *_about;
    QMenu *_file;

    GraphicsModel* _graphicsModel;
    PresentationModel* _presentationModel;
    virtual void Update(Subject* subject);
private slots:
    void MessageDialog();
    void OpenFileDialog();
    void SaveFileDialog();
    void Undo();
    void Redo();
    void DrawSquare();
    void DrawRectangle();
    void DrawCircle();
    void Group();
    void Ungroup();
    void DeleteSimpleGraphic();

    void DrawScene(vector<Graphics *> *graphicsVector) const;
};

#endif // GUI_H
#endif //HW2_GUI_H
