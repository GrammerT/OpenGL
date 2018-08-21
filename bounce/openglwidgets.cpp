#include "openglwidgets.h"
#include <QTimer>
#include <QDebug>

OpenGLWidgets::OpenGLWidgets(QWidget *parent)
    :QOpenGLWidget(parent)
    ,point_x(0.0)
    ,point_y(0.0)
    ,rectSize(25.0)
    ,xstep(1.0)
    ,ystep(1.0)

{
    QTimer *timer = new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerout()));
    timer->start(25);
}

void OpenGLWidgets::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0,0.0,1.0,1.0);
}

void OpenGLWidgets::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glRectf(point_x,point_y,point_x+rectSize,point_y-rectSize);
}

void OpenGLWidgets::resizeGL(int w, int h)
{
    GLfloat aspectRatio;
    if(h==0)
    {
        h=1;
    }
    qDebug()<<w<<"---"<<h;
    glViewport(0,0,w,h);
    //! 重置坐标系统
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat)w/(GLfloat)h;
    if(w<=h)
    {
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;
        glOrtho(-100.0,100.0,-windowHeight,windowHeight,1.0,-1.0);
    }
    else
    {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;
        glOrtho(-windowWidth,windowWidth,-100,100,1.0,-1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidgets::keyPressEvent(QKeyEvent *event)
{

}

void OpenGLWidgets::onTimerout()
{
    if(point_x>windowWidth-rectSize||point_x<-windowWidth)
    {
        point_x=-point_x;
    }
    // Reverse direction when you reach top or bottom edge
        if(point_y > windowHeight || point_y < -windowHeight + rectSize)
            ystep = -ystep;

        // Actually move the square
        point_x += xstep;
        point_y += ystep;

        // Check bounds. This is in case the window is made
        // smaller while the rectangle is bouncing and the
        // rectangle suddenly finds itself outside the new
        // clipping volume
        if(point_x > (windowWidth-rectSize + xstep))
           point_x = windowWidth-rectSize-1;
        else if(point_x < -(windowWidth+ xstep))
            point_x = -this->width() -1;

        if(point_y > (windowHeight + ystep))
            point_y = windowHeight-1;
        else if(point_y < -(windowHeight - rectSize + ystep))
            point_y = -windowHeight + rectSize - 1;
        update();
}
