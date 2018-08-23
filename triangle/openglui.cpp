#include "openglui.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QtMath>
#include "GL/glut.h"
#include <QDebug>

OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
    ,xRot(0)
    ,yRot(0)
    ,depthTest(false)
    ,cullFace(false)
    ,Counterclockwise(false)
{
    this->setFocusPolicy(Qt::StrongFocus);
    action1 = new QAction(tr("Enable depth test"),this);
    action2 = new QAction(tr("Enable cull backface"),this);
    action3 = new QAction(tr("Enable outline back"),this);
    qDebug()<< connect(action1,SIGNAL(triggered(bool)),this,SLOT(onChangeState1(bool)));
    qDebug()<< connect(action2,SIGNAL(triggered(bool)),this,SLOT(onChangeState2(bool)));
    qDebug()<< connect(action3,SIGNAL(triggered(bool)),this,SLOT(onChangeState3(bool)));

}

void OpenglUI::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction(action1);
    menu.addAction(action2);
    menu.addAction(action3);
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    menu.exec(QCursor::pos());
}

void OpenglUI::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0,0.0,0.0,1.0);

    //! 设置着色模式
    //! GL_FLAT:
    glShadeModel(GL_FLAT);
    glFrontFace(GL_CW);
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if(Counterclockwise)
    {
        glPolygonMode(GL_FRONT,GL_FILL);
    }
    else
    {
        glPolygonMode(GL_BACK,GL_LINE);
    }
    if(depthTest)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
    if(cullFace)
    {
        glEnable(GL_CULL_FACE);
//        glCullFace(GL_BACK);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }


    glPushMatrix();
    glRotatef(xRot,1.0,0.0,0.0);
    glRotatef(yRot,0.0,1.0,0.0);
    {
//        glColor3f(1.0f,0.0f,0.0f);
//        glutSolidSphere(20.0f,50,50);
    }
    glBegin(GL_TRIANGLE_FAN); //! 三角形条扇
    glVertex3f(0.0,0.0,75.0);
    int iPivot = 1;
    GLfloat begin_x = 0.0f;
    GLfloat begin_y = 20.0f;
    for(GLfloat angle = 0.0;angle<2.0f*M_PI;angle+=(M_PI/8.0f))
    {
        GLfloat x = 20.0f*qSin(angle);
        GLfloat y = 20.0f*qCos(angle);
        if(iPivot%2==0)
        {
            glColor3f(0.0,1.0,0.0);
        }
        else
        {
            glColor3f(0.0,0.0,1.0);
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
        glColor3f(0.0,0.0,1.0);
    }
    glVertex2f(begin_x,begin_y);
    glEnd();

//        glColor3f(0.0f,0.0f,1.0f);
//        glTranslatef(0.0f,0.0f,70.0f);
//        glutSolidSphere(5.0f,10,10);
//    /*
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0,0.0);
        iPivot = 1;
        for(GLfloat angle=0.0;angle<M_PI*2.0f;angle+=(M_PI/8.0f))
        {
            GLfloat x = 20.0f*qSin(angle);
            GLfloat y = 20.0f*qCos(angle);
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
    }
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
    depthTest=!depthTest;
    if(depthTest)
    {
        action1->setText("Disable depth test");
    }
    else
    {
        action1->setText("Enable depth test");
    }
}

void OpenglUI::onChangeState2(bool)
{
    cullFace=!cullFace;
    if(cullFace)
    {
        action2->setText("Disable cull backface");
    }
    else
    {
        action2->setText("Enable cull backface");
    }
}

void OpenglUI::onChangeState3(bool)
{
    Counterclockwise=!Counterclockwise;
    if(cullFace)
    {
        action3->setText("Disable outline back");
    }
    else
    {
        action3->setText("Enable outline back");
    }
}
