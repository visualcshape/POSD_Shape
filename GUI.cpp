//
// Created by VodalokLab on 2015/11/25.
//

#include "GUI.h"
#include <QFileDialog>
#include "GraphicFactory.h"
#include "DrawVisitor.h"
#include "DescriptionVisitor.h"
#include <fstream>

#define WINDOW_SIZE_WIDTH 800
#define WINDOW_SIZE_HEIGHT 600

#define SCENE_RECT_X -400
#define SCENE_RECT_Y -300

GUI::GUI()
{
    const char* TITLE = "Graphic";
    //bind to model
    GraphicsModel* graphicsModel = new GraphicsModel();
    graphicsModel->Attach(this);
    _graphicsModel = graphicsModel;
    //bind to presentation model...
    PresentationModel* presentationModel = new PresentationModel();
    presentationModel->Attach(this);
    _presentationModel = presentationModel;
    CreateView();
    CreateActions();
    CreateMenus();
    CreateToolButtons();
    SetActionConnection();
    setWindowTitle(TITLE);
    setMinimumSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
    Display();
    _presentationModel->Refresh();
}

GUI::~GUI()
{
    //Detach the from the subject
    _graphicsModel->Detach(this);
    _presentationModel->Detach(this);
    delete _widget;
    delete _scene;
    delete _graphicsModel;
    delete _presentationModel;
}

void GUI::CreateView(){
    const char* GRAPHIC_VIEW_NAME = "graphicView";
    _widget = new QWidget();
    setCentralWidget(_widget);
    _graphicsView = new QGraphicsView(_widget);
    _graphicsView->setObjectName(GRAPHIC_VIEW_NAME);

    _scene = new CustomCanvasGraphicsScene(this->_graphicsModel);
    const QRectF SCENE_RECT(SCENE_RECT_X,SCENE_RECT_Y,WINDOW_SIZE_WIDTH,WINDOW_SIZE_HEIGHT);
    _scene->setSceneRect(SCENE_RECT);

    _graphicsView->setScene(_scene);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(_graphicsView);
    _widget->setLayout(layout);
    //Not resizable
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
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
    connect(_deleteGraphic, SIGNAL(triggered()), this, SLOT(DeleteSimpleGraphic()));
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
    _deleteGraphic = new QAction(QIcon("DeleteSimpleGraphic.png"), "Delete a Graphic", _widget);
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
    qtToolBar->addAction(_deleteGraphic);
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
        try{
            _graphicsModel->loadFile(path.toStdString().c_str());
        }catch (string exceptionMessage){
            const QString MESSAGE_BOX_TITLE = "Load File Error";
            const QString MESSAGE_BOX_MESSAGE = exceptionMessage.c_str();
            QMessageBox messageBox(this);
            messageBox.setWindowTitle(MESSAGE_BOX_TITLE);
            messageBox.setText(MESSAGE_BOX_MESSAGE);
            messageBox.exec();
        }
    }
}

void GUI::SaveFileDialog() {
    QString path = QFileDialog::getSaveFileName(this,"Text Files",".","Text Files(*.txt)");
    if(path.length() != 0){
        _graphicsModel->saveFile(path.toStdString().c_str());
    }
}

void GUI::Undo() {

}

void GUI::Redo() {

}

void GUI::DrawSquare() {
    _graphicsModel->addSquareOnOriginalPoint();
}

void GUI::DrawRectangle() {
    _graphicsModel->addRectangleOnOriginalPoint();
}

void GUI::DrawCircle() {
    _graphicsModel->addCircleOnOriginalPoint();
}

void GUI::Group() {

}

void GUI::Ungroup() {

}

void GUI::DeleteSimpleGraphic() {

}

void GUI::Update(Subject *subject) {
    if(subject == _graphicsModel){
        //Draw
        DrawScene(_graphicsModel->getGraphicsVector());
        return;
    }
    if(subject == _presentationModel){
        _undo->setEnabled(_presentationModel->IsUndoEnabled());
        _redo->setEnabled(_presentationModel->IsRedoEnabled());
        _ungroup->setEnabled(_presentationModel->IsUngroupEnabled());
        _group->setEnabled(_presentationModel->IsGroupEnabled());
        _deleteGraphic->setEnabled(_presentationModel->IsDeleteGraphicEnabled());
    }
}

void GUI::DrawScene(vector<Graphics *> *graphicsVector) const {
    _scene->clear();
    for(vector<Graphics*>::iterator iterator = graphicsVector->begin() ; iterator != graphicsVector->end() ; iterator++){
        DrawVisitor drawVisitor(_scene);
        (*iterator)->accept(drawVisitor);
    }
}
