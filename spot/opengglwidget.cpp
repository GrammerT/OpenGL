#include "opengglwidget.h"
#include <QKeyEvent>
#include <gl/GLU.h>
#include "glut.h"
#include <QDebug>

OpengGLWidget::OpengGLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
    ,xRot(0.0)
    ,yRot(0.0)
{
    lightPos = QVector4D(0.0f, 0.0f, 75.0f, 1.0f) ;
    specular=  QVector4D(1.0f, 1.0f, 1.0f, 1.0f );
    specref=      QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
    ambientLight=QVector4D(0.5f, 0.5f, 0.5f, 1.0f);
    spotDir= QVector3D(0.0f, 0.0f, -1.0f);
    this->setFocusPolicy(Qt::StrongFocus);
}

void OpengGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,&ambientLight[0]);

    glLightfv(GL_LIGHT0,GL_DIFFUSE,&ambientLight[0]);
    glLightfv(GL_LIGHT0,GL_SPECULAR,&specular[0]);
    glLightfv(GL_LIGHT0,GL_POSITION,&lightPos[0]);

    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,50.0f);

    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT,GL_SPECULAR,&specref[0]);
    glMateriali(GL_FRONT,GL_SHININESS,128);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void OpengGLWidget::paintGL()
{
    glShadeModel(GL_FLAT);
//    glShadeModel(GL_SMOOTH);

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // First place the light
    // Save the coordinate transformation
    glPushMatrix();
    // Rotate coordinate system
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);

    // Specify new position and direction in rotated coords.
    glLightfv(GL_LIGHT0,GL_POSITION,&lightPos[0]);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,&spotDir[0]);

    // Draw a red cone to enclose the light source
    glColor3ub(255,0,0);

    // Translate origin to move the cone out to where the light
    // is positioned.
    qDebug()<<lightPos;
    glTranslatef(lightPos[0],lightPos[1],lightPos[2]);
    glutSolidCone(4.0f,6.0f,15,15);

    // Draw a smaller displaced sphere to denote the light bulb
    // Save the lighting state variables
    glPushAttrib(GL_LIGHTING_BIT);

    // Turn off lighting and specify a bright yellow sphere
    glDisable(GL_LIGHTING);
    glColor3ub(0,255,0);
    glutSolidSphere(3.0f, 15, 15);
    // Restore lighting state variables
    glPopAttrib();
    // Restore coordinate transformations
    glPopMatrix();
    // Set material color and draw a sphere in the middle
    glColor3ub(0, 0, 255);

    glutSolidSphere(30.0f, 7, 7);

//    glutSolidSphere(30.0f, 15, 15);
//    glutSolidSphere(30.0f, 50, 50);

}

void OpengGLWidget::resizeGL(int w, int h)
{
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Establish viewing volume
    fAspect = (GLfloat) w / (GLfloat) h;
    gluPerspective(35.0f, fAspect, 1.0f, 500.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -200.0f);
}

void OpengGLWidget::keyPressEvent(QKeyEvent *event)
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
