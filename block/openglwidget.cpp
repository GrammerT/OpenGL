#include "openglwidget.h"
#include <QKeyEvent>

OpenglWidget::OpenglWidget(QWidget *parent)
    :QOpenGLWidget(parent)
    ,m_Step(0)
{
    m_lightPos       =     {-80.0f,120.0f,100.0f,0.0f};
    m_lightAmbient   = {0.2f,0.2f,0.2f,1.0f};
    m_lightDiffuse   = {0.7f,0.7f,0.7f,1.0f};
    m_lightSpecular  = {0.9f, 0.9f, 0.9f};
    m_materialColor  = {0.8f, 0.0f, 0.0f};
    m_ground.push_back(0.0f);
    m_ground.push_back(-25.0f);
    m_ground.push_back(0.0f);
    m_ground.push_back(10.0f);
    m_ground.push_back(-25.0f);
    m_ground.push_back(0.0f);
    m_ground.push_back(10.0f);
    m_ground.push_back(-25.0f);
    m_ground.push_back(-10.0f);

}

void OpenglWidget::initializeOpenGLFunctions()
{

}

void OpenglWidget::paintGL()
{
    GLfloat cubeXform[4][4];
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glPushMatrix();
    // Draw plane that the cube rests on
    glDisable(GL_LIGHTING);
    if(m_Step == 5)
    {
        glColor3ub(255,255,255);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_textures[0]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-100.0f, -25.3f, -100.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-100.0f, -25.3f, 100.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(100.0f,  -25.3f, 100.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(100.0f,  -25.3f, -100.0f);
        glEnd();
    }
    else
    {
        glColor3f(0.0f, 0.0f, 0.90f); // Blue
        glBegin(GL_QUADS);
        glVertex3f(-100.0f, -25.3f, -100.0f);
        glVertex3f(-100.0f, -25.3f, 100.0f);
        glVertex3f(100.0f,  -25.3f, 100.0f);
        glVertex3f(100.0f,  -25.3f, -100.0f);
        glEnd();
    }
    // Set drawing color to Red
    glColor3f(1.0f, 0.0f, 0.0f);
    // Enable, disable lighting
    if(m_Step > 2)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_COLOR_MATERIAL);

        glLightfv(GL_LIGHT0, GL_AMBIENT, m_lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, m_lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, m_lightSpecular);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glMaterialfv(GL_FRONT, GL_SPECULAR,m_lightSpecular);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_materialColor);
        glMateriali(GL_FRONT, GL_SHININESS,128);
    }
    // Move the cube slightly forward and to the left
    glTranslatef(-10.0f, 0.0f, 10.0f);

    switch(m_Step)
    {
    // Just draw the wire framed cube
    case 0:
    {
//        glutWireCube(50.0f);
        break;
    }
     /*
    // Same wire cube with hidden line removal simulated
    case 1:
    {
        // Front Face (before rotation)
        glBegin(GL_LINES);
        glVertex3f(25.0f,25.0f,25.0f);
        glVertex3f(25.0f,-25.0f,25.0f);

        glVertex3f(25.0f,-25.0f,25.0f);
        glVertex3f(-25.0f,-25.0f,25.0f);

        glVertex3f(-25.0f,-25.0f,25.0f);
        glVertex3f(-25.0f,25.0f,25.0f);

        glVertex3f(-25.0f,25.0f,25.0f);
        glVertex3f(25.0f,25.0f,25.0f);
        glEnd();

        // Top of cube
        glBegin(GL_LINES);
        // Front Face
        glVertex3f(25.0f,25.0f,25.0f);
        glVertex3f(25.0f,25.0f,-25.0f);

        glVertex3f(25.0f,25.0f,-25.0f);
        glVertex3f(-25.0f,25.0f,-25.0f);

        glVertex3f(-25.0f,25.0f,-25.0f);
        glVertex3f(-25.0f,25.0f,25.0f);

        glVertex3f(-25.0f,25.0f,25.0f);
        glVertex3f(25.0f,25.0f,25.0f);
        glEnd();

        // Last two segments for effect
        glBegin(GL_LINES);
        glVertex3f(25.0f,25.0f,-25.0f);
        glVertex3f(25.0f,-25.0f,-25.0f);

        glVertex3f(25.0f,-25.0f,-25.0f);
        glVertex3f(25.0f,-25.0f,25.0f);
        glEnd();

        break;
    }
    // Uniform colored surface, looks 2D and goofey
    case 2:
    {
        glutSolidCube(50.0f);
        break;
    }
    case 3:
    {
        glutSolidCube(50.0f);
        break;
    }
    // Draw a shadow with some lighting
    case 4:
    {
        glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *) cubeXform);
        glutSolidCube(50.0f);
        glPopMatrix();

        // Disable lighting, we'll just draw the shadow as black
        glDisable(GL_LIGHTING);

        glPushMatrix();

        MakeShadowMatrix(ground, lightpos, cubeXform);
        glMultMatrixf((GLfloat *)cubeXform);

        glTranslatef(-10.0f, 0.0f, 10.0f);

        // Set drawing color to Black
        glColor3f(0.0f, 0.0f, 0.0f);

        glutSolidCube(50.0f);
        break;
    }
    case 5:
    {
        glColor3ub(255,255,255);
        glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *) cubeXform);

        // Front Face (before rotation)
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(25.0f,25.0f,25.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(25.0f,-25.0f,25.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-25.0f,-25.0f,25.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-25.0f,25.0f,25.0f);
        glEnd();

        // Top of cube
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glBegin(GL_QUADS);
        // Front Face
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(25.0f,25.0f,25.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(25.0f,25.0f,-25.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-25.0f,25.0f,-25.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-25.0f,25.0f,25.0f);
        glEnd();

        // Last two segments for effect
        glBindTexture(GL_TEXTURE_2D, textures[3]);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(25.0f,25.0f,-25.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(25.0f,-25.0f,-25.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(25.0f,-25.0f,25.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(25.0f,25.0f,25.0f);
        glEnd();


        glPopMatrix();

        // Disable lighting, we'll just draw the shadow as black
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        glPushMatrix();

        MakeShadowMatrix(ground, lightpos, cubeXform);
        glMultMatrixf((GLfloat *)cubeXform);

        glTranslatef(-10.0f, 0.0f, 10.0f);

        // Set drawing color to Black
        glColor3f(0.0f, 0.0f, 0.0f);
        glutSolidCube(50.0f);
        break;
    }
    */
    }
    glPopMatrix();
    // Flush drawing commands
//    glutSwapBuffers();
}

void OpenglWidget::resizeGL(int w, int h)
{
    // Calculate new clipping volume
    GLfloat windowWidth;
    GLfloat windowHeight;

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;

    // Keep the square square
    if (w <= h)
    {
        windowHeight = 100.0f*(GLfloat)h/(GLfloat)w;
        windowWidth = 100.0f;
    }
    else
    {
        windowWidth = 100.0f*(GLfloat)w/(GLfloat)h;
        windowHeight = 100.0f;
    }

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set the clipping volume
    glOrtho(-100.0f, windowWidth, -100.0f, windowHeight, -200.0f, 200.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightfv(GL_LIGHT0,GL_POSITION,m_lightPos);

    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(330.0f, 0.0f, 1.0f, 0.0f);
}

void OpenglWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space)
    {
        m_Step++;

        if(m_Step > 5)
            m_Step = 0;
    }
}
