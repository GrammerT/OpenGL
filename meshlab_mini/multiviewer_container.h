#ifndef MULTIVIEWER_CONTAINER_H
#define MULTIVIEWER_CONTAINER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QVector>
#include <QSplitter>
#include <QSplitterHandle>


class GLArea;
class MultiViewer_Container;
class MainWindow;

class Splitter:public QSplitter
{
    Q_OBJECT
public:
    Splitter(QWidget *parent);
    Splitter(Qt::Orientation orientation,QWidget *parent=0);
    ~Splitter();
    virtual bool isMultiViewerContainer()const{return false;}
    MultiViewer_Container *getRootContainer();
protected:
    QSplitterHandle *createHandle();
};

class MultiViewer_Container
{
public:
    MultiViewer_Container();
};

#endif // MULTIVIEWER_CONTAINER_H
