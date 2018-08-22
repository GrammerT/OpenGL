#include "openglui.h"
#include <QtMath>
#include <QKeyEvent>

OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
    ,xRot(0)
    ,yRot(0)
{
    this->setFocusPolicy(Qt::StrongFocus);
}

void OpenglUI::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void OpenglUI::paintGL()
{
    GLfloat x,y,z,angle;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(xRot,1.0f,0.0f,0.0f);
    glRotatef(yRot,0.0f,1.0f,0.0f);

    glColor3f(0.0f,1.0f,0.0f);
    z=0.0f;
    glBegin(GL_LINES);
    for(angle=0.0f;angle<=M_PI;angle+=(M_PI)/20.0f)
    {
        // Top half of the circle
        x = 50.0f*qSin(angle);
        y = 50.0f*qCos(angle);
        glVertex3f(x, y, z);

        // Bottom half of the circle
        x = 50.0f*qSin(angle+M_PI);
        y = 50.0f*qCos(angle+M_PI);
        glVertex3f(x, y, z);

    }
    glEnd();
    glPopMatrix();
}

void OpenglUI::resizeGL(int w, int h)
{
    GLfloat nRange = 100.0f;

    if(h==0)
        h=1;

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w<h)
    {
        glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w,-nRange,nRange);
    }
    else
    {
        glOrtho(-nRange*w/h,nRange*w/h,-nRange,nRange,-nRange,nRange);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void OpenglUI::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        xRot+=5.0f;
        break;
    case Qt::Key_Down:
        xRot-=5.0f;
        break;
    case Qt::Key_Left:
        yRot-=5.0f;
        break;
    case Qt::Key_Right:
        yRot+=5.0f;
        break;
    default:
        break;
    }
    if(xRot > 356.0f)
        xRot = 0.0f;

    if(xRot < -1.0f)
        xRot = 355.0f;

    if(yRot > 356.0f)
        yRot = 0.0f;

    if(yRot < -1.0f)
        yRot = 355.0f;

    update();
}
