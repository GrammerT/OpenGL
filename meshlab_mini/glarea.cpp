#include "glarea.h"
#include "multiviewer_container.h"

GLArea::GLArea(QWidget *parent, MultiViewer_Container *mvcont)
    :QOpenGLWidget(parent,mvcont->sharedDataContext())
{

}

GLArea::~GLArea()
{

}

void GLArea::initializeGL()
{

}

void GLArea::paintEvent(QPaintEvent *e)
{

}

void GLArea::keyReleaseEvent(QKeyEvent *e)
{

}

void GLArea::keyPressEvent(QKeyEvent *e)
{

}

void GLArea::mousePressEvent(QMouseEvent *event)
{

}

void GLArea::mouseMoveEvent(QMouseEvent *event)
{

}

void GLArea::mouseReleaseEvent(QMouseEvent *event)
{

}

void GLArea::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void GLArea::wheelEvent(QWheelEvent *e)
{

}

void GLArea::tabletEvent(QTabletEvent *e)
{

}

void GLArea::hideEvent(QHideEvent *event)
{

}
