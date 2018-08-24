#include "openglui.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QDebug>

// Flags for effects
#define MODE_SOLID 0
#define MODE_LINE  1
#define MODE_POINT 2

int iMode = MODE_SOLID;
GLboolean bEdgeFlag = true;

OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
    ,xRot(0)
    ,yRot(0)
{
    this->setFocusPolicy(Qt::StrongFocus);
    QAction *action1mode_solid = new QAction(tr("Solid"),this);
    QAction *action2mode_line = new QAction(tr("Outline"),this);
    QAction *action3mode_point = new QAction(tr("Point"),this);
    qDebug()<< connect(action1mode_solid,SIGNAL(triggered(bool)),this,SLOT(onChangeState1(bool)));
    qDebug()<< connect(action2mode_line,SIGNAL(triggered(bool)),this,SLOT(onChangeState2(bool)));
    qDebug()<< connect(action3mode_point,SIGNAL(triggered(bool)),this,SLOT(onChangeState3(bool)));
    QAction *action2Edge_on = new QAction(tr("On"),this);
    QAction *action3Edge_off = new QAction(tr("Off"),this);
    qDebug()<< connect(action2Edge_on,SIGNAL(triggered(bool)),this,SLOT(onChangeStateEdgeOn(bool)));
    qDebug()<< connect(action3Edge_off,SIGNAL(triggered(bool)),this,SLOT(onChangeStateEdgeOff(bool)));
}

void OpenglUI::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    QMenu menu1(tr("Mode"));
    QMenu menu2(tr("Edge"));

    QAction *action1mode_solid = new QAction(tr("Solid"),this);
    QAction *action2mode_line = new QAction(tr("Outline"),this);
    QAction *action3mode_point = new QAction(tr("Point"),this);
    qDebug()<< connect(action1mode_solid,SIGNAL(triggered(bool)),this,SLOT(onChangeState1(bool)));
    qDebug()<< connect(action2mode_line,SIGNAL(triggered(bool)),this,SLOT(onChangeState2(bool)));
    qDebug()<< connect(action3mode_point,SIGNAL(triggered(bool)),this,SLOT(onChangeState3(bool)));
    QAction *action2Edge_on = new QAction(tr("On"),this);
    QAction *action3Edge_off = new QAction(tr("Off"),this);
    qDebug()<< connect(action2Edge_on,SIGNAL(triggered(bool)),this,SLOT(onChangeStateEdgeOn(bool)));
    qDebug()<< connect(action3Edge_off,SIGNAL(triggered(bool)),this,SLOT(onChangeStateEdgeOff(bool)));
    menu1.addAction(action1mode_solid);
    menu1.addAction(action2mode_line);
    menu1.addAction(action3mode_point);
    menu2.addAction(action2Edge_on);
    menu2.addAction(action3Edge_off);
    menu.addMenu(&menu1);
    menu.addMenu(&menu2);
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    menu.exec(QCursor::pos());
    delete action1mode_solid;
    delete action2mode_line;
    delete action3mode_point;
    delete action2Edge_on;
    delete action3Edge_off;

}

void OpenglUI::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0,0.0,0.0,1.0);
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(xRot,1.0,0.0,0.0);
    glRotatef(yRot,0.0,1.0,0.0);




    glPopMatrix();
}

void OpenglUI::resizeGL(int w, int h)
{
    GLfloat glwidth = 100;
    if(h==0)
        h=1;
    GLfloat as = (GLfloat)w/(GLfloat)h;

    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<h)
    {
        glOrtho(-glwidth,glwidth,-glwidth/as,glwidth/as,-glwidth,glwidth);
    }
    else
    {
        glOrtho(-glwidth*as,glwidth*as,-glwidth,glwidth,-glwidth,glwidth);
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

void OpenglUI::onChangeState1(bool)
{
    iMode = MODE_SOLID;
}

void OpenglUI::onChangeState2(bool)
{
    iMode = MODE_LINE;
}

void OpenglUI::onChangeState3(bool)
{
    iMode = MODE_POINT;
}

void OpenglUI::onChangeStateEdgeOn(bool)
{
    bEdgeFlag = true;
}

void OpenglUI::onChangeStateEdgeOff(bool)
{
    bEdgeFlag = false;
}
