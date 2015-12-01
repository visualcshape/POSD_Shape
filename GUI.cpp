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
    Display();
    _loadedGraphics = 0;
}

GUI::~GUI()
{
    delete _widget;
    delete _scene;
    delete _loadedGraphics;
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
}

void GUI::CreateActions() {
    QIcon* aboutIcon = new QIcon("About.png");
    _aboutDeveloper = new QAction(*aboutIcon, "About Developer", _widget);
    QIcon* openFileIcon = new QIcon("Open.png");
    _openFile = new QAction(*openFileIcon, "Open File", _widget);
    QIcon* saveFileIcon = new QIcon("Save.png");
    _saveFile = new QAction(*saveFileIcon, "Save File", _widget);
}

void GUI::CreateToolButtons() {
    QToolBar* qtToolBar = new QToolBar(_widget);
    qtToolBar->addAction(_openFile);
    qtToolBar->addAction(_saveFile);
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
        _scene->clear();
        GraphicsFactory factory;
        Graphics* graphics = factory.buildGraphicsFromFile(path.toStdString().c_str());
        DrawVisitor drawVisitor(_scene);
        graphics->accept(drawVisitor);
        _loadedGraphics = graphics;
    }
}

void GUI::SaveFileDialog() {
    QString path = QFileDialog::getSaveFileName(this,"Text Files",".","Text Files(*.txt)");
    if(path.length() != 0){
        if(_loadedGraphics!=0){
            DescriptionVisitor descriptionVisitor;
            _loadedGraphics->accept(descriptionVisitor);
            fstream fs;
            fs.open(path.toStdString().c_str(),std::fstream::out);
            fs << descriptionVisitor.getDescription();
            fs.close();
        }
    }
}