#include "openglui.h"
#include <QKeyEvent>

OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
{
    xRot = 0.0;
    yRot = 0.0;
    this->setFocusPolicy(Qt::StrongFocus);
}

void OpenglUI::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f,1.0f,0.0f);

    glPushMatrix();

    glRotatef(xRot,1.0,0.0,0.0);
    glRotatef(yRot,0.0,1.0,0.0);
    GLfloat fSizes[2];			// Line width range metrics
    GLfloat fCurrSize;			// Save current size
    glGetFloatv(GL_LINE_WIDTH_RANGE,fSizes);
    fCurrSize = fSizes[0];

    // Step up Y axis 20 units at a time
    for(GLfloat y = -90.0f; y < 90.0f; y += 20.0f)
    {
        // Set the line width
        glLineWidth(fCurrSize);
        // Draw the line
        glBegin(GL_LINES);
        glVertex2f(-80.0f, y);
        glVertex2f(80.0f, y);
        glEnd();
        // Increase the line width
        fCurrSize += 1.0f;
    }

    glPopMatrix();
}

void OpenglUI::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);

    if(h==0)
        h=1;
    GLfloat glwidth=100.0f;
    GLfloat as = (GLfloat)w/(GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w>=h)
    {
        glOrtho(-glwidth*as,glwidth*as,-glwidth,glwidth,-100,100);
    }
    else
    {
        glOrtho(-glwidth,glwidth,-glwidth/as,glwidth/as,-100,100);
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
