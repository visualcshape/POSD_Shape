//
// Created by VodalokLab on 2015/11/25.
//

#include "GUI.h"
#include <QFileDialog>
#include "GraphicFactory.h"
#include "DrawVisitor.h"
#include "DescriptionVisitor.h"
#include <fstream>

GUI::GUI()
{
    CreateView();
    CreateActions();
    CreateMenus();
    CreateToolButtons();
    SetActionConnection();
    QString title = "Graphics";
    setWindowTitle(title);
    setMinimumSize(800, 600);
    //setupInitialState();
    Display();
}

GUI::~GUI()
{
    delete _widget;
    delete _scene;
}

void GUI::CreateView(){
    _widget = new QWidget();
    setCentralWidget(_widget);
    _graphicsView = new QGraphicsView(_widget);
    QString gView = "graphicView";
    _graphicsView->setObjectName(gView);

    _scene = new QGraphicsScene();

    _graphicsView->setScene(_scene);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(_graphicsView);
    _widget->setLayout(layout);
}

void GUI::SetActionConnection() {
    connect(_aboutDeveloper, SIGNAL(triggered()), this, SLOT(MessageDialog()));
    connect(_openFile, SIGNAL(triggered()), this, SLOT(OpenFileDialog()));
    connect(_saveFile, SIGNAL(triggered()), this, SLOT(SaveFileDialog()));
    connect(_undo,SIGNAL(triggered()),this,SLOT(Undo()));
    connect(_redo,SIGNAL(triggered()),this,SLOT(Redo()));
    connect(_drawSquare,SIGNAL(triggered()),this,SLOT(DrawSquare()));
    connect(_drawRectangle,SIGNAL(triggered()),this,SLOT(DrawRectangle()));
    connect(_drawCircle,SIGNAL(triggered()),this,SLOT(DrawCircle()));
    connect(_group,SIGNAL(triggered()),this,SLOT(Group()));
    connect(_ungroup,SIGNAL(triggered()),this,SLOT(Ungroup()));
    connect(_deleteSimpleGraphic,SIGNAL(triggered()),this,SLOT(DeleteSimpleGraphic()));
}

void GUI::CreateActions() {
    QIcon* aboutIcon = new QIcon("About.png");
    _aboutDeveloper = new QAction(*aboutIcon, "About Developer", _widget);
    QIcon* openFileIcon = new QIcon("Open.png");
    _openFile = new QAction(*openFileIcon, "Open File", _widget);
    QIcon* saveFileIcon = new QIcon("Save.png");
    _saveFile = new QAction(*saveFileIcon, "Save File", _widget);
    QIcon squareIcon("Square.png");
    _drawSquare = new QAction(squareIcon,"Draw Square", _widget);
    QIcon* drawRectangleIcon = new QIcon("Rectangle.png");
    _drawRectangle = new QAction(*drawRectangleIcon,"Draw Rectangle",_widget);
    QIcon* drawCircleIcon = new QIcon("Circle.png");
    _drawCircle = new QAction(*drawCircleIcon,"Draw Circle",_widget);
    QIcon undoIcon("undo.png");
    _undo = new QAction(undoIcon,"Undo",_widget);
    QIcon redoIcon("redo.png");
    _redo = new QAction(redoIcon,"Redo",_widget);
    _group = new QAction(QIcon("Group.png"),"Group",_widget);
    _ungroup = new QAction(QIcon("Ungroup.png"),"Ungroup",_widget);
    _deleteSimpleGraphic = new QAction(QIcon("DeleteSimpleGraphic.png"),"Delete a Graphic",_widget);
}

void GUI::CreateToolButtons() {
    QToolBar* qtToolBar = new QToolBar(_widget);
    qtToolBar->addAction(_openFile);
    qtToolBar->addAction(_saveFile);
    qtToolBar->addSeparator();
    qtToolBar->addAction(_undo);
    qtToolBar->addAction(_redo);
    qtToolBar->addSeparator();
    qtToolBar->addAction(_drawRectangle);
    qtToolBar->addAction(_drawCircle);
    qtToolBar->addAction(_drawSquare);
    qtToolBar->addSeparator();
    qtToolBar->addAction(_group);
    qtToolBar->addAction(_ungroup);
    qtToolBar->addSeparator();
    qtToolBar->addAction(_deleteSimpleGraphic);
    //Adjust the toolbar size
    qtToolBar->setFixedWidth(1000);
}

void GUI::CreateMenus() {
    _file = this->menuBar()->addMenu("File");
    _file->addAction(_openFile);
    _file->addAction(_saveFile);
    _about = menuBar()->addMenu("About");
    _about->addAction(_aboutDeveloper);
}
void GUI::Display() {

}

void GUI::MessageDialog() {
    QMessageBox msgbox;
    std::string message("104598013\n");
    message += std::string("Author : Chi-Chia Sun\n");
    QString qstr = QString::fromStdString(message);
    msgbox.setText(qstr);
    msgbox.exec();
}

void GUI::OpenFileDialog() {
    QString path = QFileDialog::getOpenFileName(this,"Text Files",".","Text Files(*.txt)");
    if(path.length() != 0){
        /*
        GraphicsFactory factory;
        Graphics* graphics = factory.buildGraphicsFromFile(path.toStdString().c_str());
        DrawVisitor drawVisitor(_scene);
        graphics->accept(drawVisitor);
        */

        vector<Graphics*>* multiRootsGraphicVector = 0;
        GraphicsFactory graphicsFactory;
        multiRootsGraphicVector = graphicsFactory.buildMultiRootGraphicsFromFile(path.toStdString().c_str());
        for(vector<Graphics*>::iterator itr = multiRootsGraphicVector->begin() ; itr != multiRootsGraphicVector->end() ; itr++){
            DrawVisitor drawVisitor(_scene);
            (*itr)->accept(drawVisitor);
        }

        cout << graphicsFactory.getLastSnapShot() << endl;
    }
}

void GUI::SaveFileDialog() {
    QString path = QFileDialog::getSaveFileName(this,"Text Files",".","Text Files(*.txt)");
    if(path.length() != 0){
        
    }
}

void GUI::setupInitialState() {
    _undo->setEnabled(false);
    _redo->setEnabled(false);
    _deleteSimpleGraphic->setEnabled(false);
    _group->setEnabled(false);
    _ungroup->setEnabled(false);
}

void GUI::Undo() {

}

void GUI::Redo() {

}

void GUI::DrawSquare() {

}

void GUI::DrawRectangle() {

}

void GUI::DrawCircle() {

}

void GUI::Group() {

}

void GUI::Ungroup() {

}

void GUI::DeleteSimpleGraphic() {

}
