#include "openglui.h"
#include "glut.h"

OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
{

}

void OpenglUI::initializeGL()
{
    initializeOpenGLFunctions();
    // set color used to clear background
    glClearColor(0.1f, 0.1f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    // view matrix
//    view.setToIdentity();
//    view.lookAt(QVector3D(0.0f, 0.0f, 3.0f), QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,1.0f,0.0f));
    gluLookAt(0.0f, 0.0f, 50.0f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0.0,0.0,-9.0);
    glutSolidSphere(20,6,6);
    glPopMatrix();
}

void OpenglUI::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
//    projection.setToIdentity();
//    projection.perspective(60.0f, (GLfloat)w/(GLfloat)h, 0.001f, 100.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (GLfloat)w/(GLfloat)h, 0.001f, 100.0f);
}
