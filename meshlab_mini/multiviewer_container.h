#ifndef MULTIVIEWER_CONTAINER_H
#define MULTIVIEWER_CONTAINER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QVector>
#include <QSplitter>
#include <QSplitterHandle>
#include "meshmodel.h"


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

class MultiViewer_Container:public Splitter
{
    Q_OBJECT
public:
    MultiViewer_Container(QWidget *parent);
    ~MultiViewer_Container();
    GLArea* currentView();
    void addView(GLArea *viewer, Qt::Orientation ori);

    GLArea* getViewer(int id);

    int viewerCounter();
    void update(int id);

    inline QOpenGLWidget *sharedDataContext(){return scenecontext;}

public slots:
    void updateCurrent(int current);

public:
    MeshDocument meshDoc;
    QOpenGLWidget *scenecontext;
    GLArea *currentgla;
    int currentId;
private:
    QList<GLArea*> viewerList;
};

#endif // MULTIVIEWER_CONTAINER_H
