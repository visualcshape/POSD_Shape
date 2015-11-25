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
    delete widget;
    delete scene;
    delete _loadedGraphics;
}

void GUI::CreateView(){
    widget = new QWidget();
    setCentralWidget(widget);
    graphicsView = new QGraphicsView(widget);
    QString gView = "graphicView";
    graphicsView->setObjectName(gView);

    scene = new QGraphicsScene();

    graphicsView->setScene(scene);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(graphicsView);
    widget->setLayout(layout);
}

void GUI::SetActionConnection() {
    connect(aboutDeveloper, SIGNAL(triggered()), this, SLOT(MessageDialog()));
    connect(openFile,SIGNAL(triggered()),this,SLOT(OpenFileDialog()));
    connect(saveFile,SIGNAL(triggered()),this,SLOT(SaveFileDialog()));
}

void GUI::CreateActions() {
    QIcon* aboutIcon = new QIcon("About.png");
    aboutDeveloper = new QAction(*aboutIcon,"About Developer", widget);
    QIcon* openFileIcon = new QIcon("Open.png");
    openFile = new QAction(*openFileIcon,"Open File",widget);
    QIcon* saveFileIcon = new QIcon("Save.png");
    saveFile = new QAction(*saveFileIcon,"Save File",widget);
}

void GUI::CreateToolButtons() {
    QToolBar* qtToolBar = new QToolBar(widget);
    qtToolBar->addAction(openFile);
    qtToolBar->addAction(saveFile);
}

void GUI::CreateMenus() {
    file = this->menuBar()->addMenu("File");
    file->addAction(openFile);
    file->addAction(saveFile);
    about = menuBar()->addMenu("About");
    about->addAction(aboutDeveloper);
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
        scene->clear();
        GraphicsFactory factory;
        Graphics* graphics = factory.buildGraphicsFromFile(path.toStdString().c_str());
        DrawVisitor drawVisitor(scene);
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