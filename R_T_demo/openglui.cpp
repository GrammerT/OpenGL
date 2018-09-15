#include "openglui.h"
#include <QDebug>
#include <QtMath>
#include <QKeyEvent>
#include <QTimer>
#include "GL/GLU.h"


OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
    ,zRotate(0)
{
//    QTimer *time = new QTimer();
//    connect(time,SIGNAL(timeout()),this,SLOT(onTimeout()));
    this->setFocusPolicy(Qt::StrongFocus);
}


void OpenglUI::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glEnable(GL_DEPTH_TEST);
}


void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    drawAxis(15.0);
    glPushMatrix();
    glTranslatef(-1.0,0.0,0.0);         //! 最后移动至目的地
    glRotatef(zRotate,0.0,0.0,1.0); //! 再旋转
    glTranslatef(-0.5,-0.5,0.0);    //! 先移动至原点

    drawAxis(3.0);
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,-5.0);
    glVertex3f(0.0,1.0,-5.0);
    glVertex3f(1.0,1.0,-5.0);
    glVertex3f(1.0,0.0,-5.0);
    glEnd();
    glPopMatrix();
}

void OpenglUI::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;
   glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspect,zNear,zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenglUI::keyPressEvent(QKeyEvent *event)
{

}

void OpenglUI::mousePressEvent(QMouseEvent *e)
{

}

void OpenglUI::mouseMoveEvent(QMouseEvent *event)
{
    zRotate++;
    if(zRotate>360)
    {
        zRotate = 0;
    }
    update();
}

void OpenglUI::wheelEvent(QWheelEvent *event)
{

}

void OpenglUI::drawAxis(float length)
{
    glPushMatrix();
        glLineWidth(3.0);
        glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(-length/2,0.0,-5.0);
        glVertex3f(length/2,0.0,-5.0);
        glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(0.0,-length/2,-5.0);
        glVertex3f(0.0,length/2,-5.0);
        glEnd();
    glPopMatrix();
}
