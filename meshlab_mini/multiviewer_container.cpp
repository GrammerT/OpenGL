#include "multiviewer_container.h"
#include "glarea.h"
#include <QList>
#include <QOpenGLWidget>

MultiViewer_Container::MultiViewer_Container(QWidget *parent)
    :Splitter(parent)
    ,meshDoc()
{
    setChildrenCollapsible(false);
    scenecontext = new QOpenGLWidget();
    scenecontext->setHidden(true);
    scenecontext->initializeGL();
    currentId=-1;
    currentgla = NULL;
}

MultiViewer_Container::~MultiViewer_Container()
{
    delete scenecontext;
}

GLArea *MultiViewer_Container::currentView()
{
    return getViewer(currentId);
}

void MultiViewer_Container::addView(GLArea *viewer, Qt::Orientation ori)
{
    if(viewerCounter()==0)
    {
        viewerList.append(viewer);
        addWidget(viewer);
        updateCurrent(viewer->getId());
    }
}

GLArea *MultiViewer_Container::getViewer(int id)
{
    foreach ( GLArea* viewer, viewerList)
        if ((viewer != NULL) && (viewer->getId() == id))
            return viewer;
    return 0;
}

int MultiViewer_Container::viewerCounter()
{
    return viewerList.count();
}

void MultiViewer_Container::update(int id)
{
    getViewer(id)->update();
}

void MultiViewer_Container::updateCurrent(int current)
{
    int previousCurrentId = currentId;
    currentId = current;
    currentgla = getViewer(currentId);
    if(getViewer(previousCurrentId))
        update(previousCurrentId);
//    emit updateMainWindowMenus();
//    if (current != previousCurrentId)
//        emit updateDocumentViewer();
}

Splitter::Splitter(QWidget *parent)
{

}

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent)
{

}

Splitter::~Splitter()
{

}

MultiViewer_Container *Splitter::getRootContainer()
{
    return NULL;
}

QSplitterHandle *Splitter::createHandle()
{
    return NULL;
}
