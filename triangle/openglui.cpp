#include "openglui.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QtMath>

OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
    ,xRot(0)
    ,yRot(0)
{
    this->setFocusPolicy(Qt::StrongFocus);
    action1 = new QAction(tr("Toggle depth test"),this);
    action2 = new QAction(tr("Toggle cull backface"),this);
    action3 = new QAction(tr("Toggle outline back"),this);
    connect(action1,SIGNAL(toggled(bool)),this,SLOT(onChangeState1(bool)));
    connect(action2,SIGNAL(toggled(bool)),this,SLOT(onChangeState2(bool)));
    connect(action3,SIGNAL(toggled(bool)),this,SLOT(onChangeState3(bool)));

}

void OpenglUI::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction(action1);
    menu.addAction(action2);
    menu.addAction(action3);
//    spreadsheet->setContextMenuPolicy(Qt::DefaultContextMenu);
    menu.exec(QCursor::pos());
}

void OpenglUI::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0,0.0,0.0,1.0);

    //! 设置着色模式
    //! GL_FLAT:
    glShadeModel(GL_FLAT);
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(xRot,1.0,0.0,0.0);
    glRotatef(yRot,0.0,1.0,0.0);

    glBegin(GL_TRIANGLE_FAN); //! 三角形条扇
    glVertex3f(0.0,0.0,75.0);
    int iPivot = 1;
    GLfloat begin_x = 0.0f;
    GLfloat begin_y = 50.0f;
    for(GLfloat angle = 0.0;angle<2.0f*M_PI;angle+=(M_PI/8.0f))
    {
        GLfloat x = 50.0f*qSin(angle);
        GLfloat y = 50.0f*qCos(angle);
        if(iPivot%2==0)
        {
            glColor3f(0.0,1.0,0.0);
        }
        else
        {
            glColor3f(1.0,0.0,0.0);
        }
        iPivot++;
        glVertex2f(x,y);
    }
    if(iPivot%2==0)
    {
        glColor3f(0.0,1.0,0.0);
    }
    else
    {
        glColor3f(1.0,0.0,0.0);
    }
    glVertex2f(begin_x,begin_y);
    glEnd();

//    /*
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(0.0,0.0);
    iPivot = 1;
    for(GLfloat angle=0.0;angle<M_PI*2.0f;angle+=(M_PI/8.0f))
    {
        GLfloat x = 50.0f*qSin(angle);
        GLfloat y = 50.0f*qCos(angle);
        if(iPivot%2==0)
        {
            glColor3f(0.0,1.0,0.0);
        }
        else
        {
            glColor3f(1.0,0.0,0.0);
        }
        iPivot++;
        glVertex2f(x,y);
    }
    if(iPivot%2==0)
    {
        glColor3f(0.0,1.0,0.0);
    }
    else
    {
        glColor3f(1.0,0.0,0.0);
    }
    glVertex2f(begin_x,begin_y);
    glEnd();
//    */

    glPopMatrix();
}

void OpenglUI::resizeGL(int w, int h)
{
    if(h==0)
        h=1;

    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat glwidth = 100.0f;
    GLfloat as = (GLfloat)w/(GLfloat)h;
    if(w<=h)
    {
        glOrtho(-glwidth,glwidth,-glwidth/as,glwidth/as,-100,100);
    }
    else
    {
        glOrtho(-glwidth*as,glwidth*as,-glwidth,glwidth,-100,100);
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

}

void OpenglUI::onChangeState2(bool)
{

}

void OpenglUI::onChangeState3(bool)
{

}
