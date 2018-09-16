#include "openglui.h"
#include <QDebug>
#include <QtMath>
#include <QKeyEvent>
#include <QTimer>
#include "GL/GLU.h"
#include "GL/glut.h"


GLfloat oneStairs[]={2.5,1.25,0.0,
                                2.5,-1.25,0.0,
                                -2.5,-1.25,0.0,
                                -2.5,1.25,0.0,
                             2.5,1.25,-2.5,
                            2.5,-1.25,-2.5,
                             -2.5,-1.25,-2.5,
                            -2.5,1.25,-2.5};

GLfloat nor[]={
    0.0,0.0,1.0,
    0.0,0.0,1.0,

    0.0,1.0,0.0,
    0.0,1.0,0.0,

    0.0,0.0,-1.0,
    0.0,0.0,-1.0,

    0.0,-1.0,0.0,
    0.0,-1.0,0.0,

    1.0,0.0,0.0,
    1.0,0.0,0.0,

    -1.0,0.0,0.0,
    -1.0,0.0,0.0,
};

GLint stairsIndex[] = {
    0,2,1,
    0,3,2,

    0,4,3,
    4,7,3,

    5,7,4,
    5,6,7,

    5,1,6,
    1,2,6,

    0,1,4,
    4,1,5,

    3,7,6,
    6,2,3
};


static GLfloat light1pos[] = { 0.0, 0.0, -2.0, 0.0 };

static GLfloat light1angle = 0.0;


OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
    ,zRotate(0)
    ,vertextVBO(0)
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
    glShadeModel(GL_FLAT);

    //! draw stair;
    glGenBuffers(1,&vertextVBO);
    glBindBuffer(GL_ARRAY_BUFFER,vertextVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(oneStairs),
                 oneStairs,
                 GL_DYNAMIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);

    glGenBuffers(1,&vertextIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vertextIBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(stairsIndex),
                 stairsIndex,
                 GL_STATIC_DRAW);

    //! 设置光照

    GLfloat light_position[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat light_ambient [] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse [] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT , light_ambient );
    glLightfv(GL_LIGHT0, GL_DIFFUSE , light_diffuse );
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    GLfloat mat_ambient[]   = {0.0f, 0.0f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT,    mat_ambient);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}


void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-5.0);
    glRotatef(zRotate,0.0,1.0,0.0);
    glDisable(GL_LIGHTING);
    drawAxis(15);
    glEnable(GL_LIGHTING);
//    drawStairs();
    drawSolarSystem();
}

void OpenglUI::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 2, zFar = 1000.0, fov = 60.0;
   glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,aspect,zNear,zFar);
    gluLookAt(0.0,0.0,270.0,0.0,0.0,0.0,0.0,1.0,0.0);
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

void OpenglUI::drawRectRotateRectOrigin()
{
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

void OpenglUI::drawStairs()
{
    glTranslatef(0.0,-5.0,2.0);
    glRotatef(30,0.0,0.0,1.0);
    glPushMatrix();
    for(int i=0;i<10;i++)
    {
        drawOneLevel();
        glPushMatrix();
            glTranslatef(-1.85,4.25,0.0);
            glScalef(0.2,1.0,0.2);
            drawHandRail();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(1.85,4.25,0.0);
            glScalef(0.2,1.0,0.2);
            drawHandRail();
        glPopMatrix();
        glTranslatef(0.0,2.5,-2.5);
    }
    glPopMatrix();
}

void OpenglUI::drawOneLevel()
{
//    glPushMatrix();
    glDisable(GL_LIGHTING);
    drawAxis(4);
    glEnable(GL_LIGHTING);

    GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的环境光颜色，为0
    GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的漫反射光颜色，为0
    GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，为0
    GLfloat sun_mat_emission[] = {0.8f, 0.0f, 0.0f, 1.0f};   //定义材质的辐射广颜色，为偏红色
    GLfloat sun_mat_shininess   = 0.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);


    glBindBuffer(GL_ARRAY_BUFFER, vertextVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vertextIBO);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, nor);

    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
//    glPopMatrix();
}

void OpenglUI::drawHandRail()
{
//    glColor3f(0.0,1.0,1.0);

    GLfloat earth_mat_ambient[]   = {0.0f, 0.0f, 1.0f, 1.0f};  //定义材质的环境光颜色，骗蓝色
    GLfloat earth_mat_diffuse[]   = {0.0f, 0.0f, 0.5f, 1.0f};  //定义材质的漫反射光颜色，偏蓝色
    GLfloat earth_mat_specular[] = {1.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，红色
    GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的辐射光颜色，为0
    GLfloat earth_mat_shininess   = 30.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
    glutSolidCube(6);
}

void OpenglUI::drawSolarSystem()
{
    GLfloat earth_mat_ambient[]   = {1.0f, 0.0f, 0.0f, 1.0f};  //定义材质的环境光颜色
    GLfloat earth_mat_diffuse[]   = {1.0f, 0.0f, 0.0f, 1.0f};  //定义材质的漫反射光颜色
    GLfloat earth_mat_specular[] = {1.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，红色
    GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的辐射光颜色，为0
    GLfloat earth_mat_shininess   = 30.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);

    glDisable(GL_LIGHTING);
    drawAxis(70);
    glEnable(GL_LIGHTING);
    glutSolidSphere(30,10,10);
    glPushMatrix();
            glRotatef(zRotate,0.0,1.0,0.0);
            glTranslatef(0.0,0.0,-75.0);
            glRotatef(zRotate+2,0.0,1.0,0.0);
            drawEarth();
        glPushMatrix();
            glRotatef(zRotate,0.0,1.0,0.0);
            glTranslatef(0.0,0.0,-25.0);
            glRotatef(zRotate+5,0.0,1.0,0.0);
            drawMoon();
        glPopMatrix();
    glPopMatrix();
}

void OpenglUI::drawEarth()
{
    GLfloat earth_mat_ambient[]   = {0.0f, 1.0f, 0.0f, 1.0f};  //定义材质的环境光颜色
    GLfloat earth_mat_diffuse[]   = {0.0f, 1.0f, 0.0f, 1.0f};  //定义材质的漫反射光颜色
    GLfloat earth_mat_specular[] = {1.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，红色
    GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的辐射光颜色，为0
    GLfloat earth_mat_shininess   = 30.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
    glDisable(GL_LIGHTING);
    drawAxis(45);
    glEnable(GL_LIGHTING);
    glutSolidSphere(20,10,10);
}

void OpenglUI::drawMoon()
{
    GLfloat earth_mat_ambient[]   = {0.0f, 1.0f, 1.0f, 1.0f};  //定义材质的环境光颜色
    GLfloat earth_mat_diffuse[]   = {0.0f, 1.0f, 1.0f, 1.0f};  //定义材质的漫反射光颜色
    GLfloat earth_mat_specular[] = {1.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，红色
    GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的辐射光颜色，为0
    GLfloat earth_mat_shininess   = 30.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
    glDisable(GL_LIGHTING);
    drawAxis(25);
    glEnable(GL_LIGHTING);
    glutSolidSphere(10,10,10);
}


