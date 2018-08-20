#include "openglwidget.h"
#include <QKeyEvent>
#include "GL/glut.h"


OpenglWidget::OpenglWidget(QWidget *parent)
    :QOpenGLWidget(parent)
    ,m_Step(0)
{
    m_lightPos[0]=-80.0;
    m_lightPos[1]=120.0;
    m_lightPos[2]=100.0;
    m_lightPos[3]=0.0;

    m_lightAmbient[0] = 0.2f;
    m_lightAmbient[1] = 0.2f;
    m_lightAmbient[2] = 0.2f;
    m_lightAmbient[3] = 1.0f;

    m_lightDiffuse[0] = 0.7f;
    m_lightDiffuse[1] = 0.7f;
    m_lightDiffuse[2] = 0.7f;
    m_lightDiffuse[3] = 1.0f;

    m_lightSpecular[0] = 0.9f;
    m_lightSpecular[1] = 0.9f;
    m_lightSpecular[2] = 0.9f;

    m_materialColor[0] = 0.8f;
    m_materialColor[1] = 0.0f;
    m_materialColor[2] = 0.0f;


    m_ground.push_back(0.0f);
    m_ground.push_back(-25.0f);
    m_ground.push_back(0.0f);
    m_ground.push_back(10.0f);
    m_ground.push_back(-25.0f);
    m_ground.push_back(0.0f);
    m_ground.push_back(10.0f);
    m_ground.push_back(-25.0f);
    m_ground.push_back(-10.0f);

    this->setFocusPolicy(Qt::StrongFocus);

}

void OpenglWidget::initPoints()
{
    //up
    m_points.push_back(QVector3D(25.0,25.0,25.0));
    m_points.push_back(QVector3D(25.0,25.0,-25.0));
    m_points.push_back(QVector3D(-25.0,25.0,-25.0));
    m_points.push_back(QVector3D(-25.0,25.0,25.0));
    // down
    m_points.push_back(QVector3D(25.0,-25.0,25.0));
    m_points.push_back(QVector3D(25.0,-25.0,-25.0));
    m_points.push_back(QVector3D(-25.0,-25.0,-25.0));
    m_points.push_back(QVector3D(-25.0,-25.0,25.0));

    QVector<QVector3D> m_plateArray;
    m_plateArray.push_back(QVector3D(-100.0f,-25.3f,-100.0f));
    m_plateArray.push_back(QVector3D(-100.0f, -25.3f, 100.0f));
    m_plateArray.push_back(QVector3D(100.0f,  -25.3f, 100.0f));
    m_plateArray.push_back(QVector3D(100.0f,  -25.3f, -100.0f));

    GLushort plateIndexs[] = {
    0,  1,  2,  3
};



    GLushort indexs[] = {
         0,  1,  2,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         0,  3,  7,  4, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         0,  4,  5, 1, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        1, 5, 6, 2, // Face 3 - triangle strip (v12, v13, v14, v15)
        3, 2, 6, 7, // Face 4 - triangle strip (v16, v17, v18, v19)
        4, 7, 6, 5      // Face 5 - triangle strip (v20, v21, v22, v23)
    };
//    // Generate 2 VBOs
//    m_arrayBuf.create();
//    m_indexBuf.create();
//    //! Transfer vertex data to VBO 0
//    m_arrayBuf.bind();
//    qDebug()<<sizeof(QVector3D);
//    m_arrayBuf.allocate(&m_points.toStdVector(), 8 * sizeof(QVector3D));

//    //! Transfer index data to VBO 1
//    m_indexBuf.bind();
//    m_indexBuf.allocate(indexs, 34 * sizeof(GLushort));


}

void OpenglWidget::initShader()
{
    // Compile vertex shader
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Link shader pipeline
    if (!m_program.link())
        close();
    // Bind shader pipeline for use
    if (!m_program.bind())
        close();

}

void OpenglWidget::initializeGL()
{
    initializeOpenGLFunctions();
//    initShader();
//    initPoints();

    glClearColor(0, 0, 0, 1);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

}

void OpenglWidget::paintGL()
{
    GLfloat cubeXform[4][4];
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH); //! default is GL_SMOOTH
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
        drawPlate();
    }
    // Set drawing color to Red
    glColor3f(1.0f, 0.0f, 0.0f);
    // Enable, disable lighting
    // Move the cube slightly forward and to the left
    glTranslatef(-10.0f, 0.0f, 10.0f);
    switch(m_Step)
    {
    // Just draw the wire framed cube
    case 0:
    {
        glutWireCube(50.0f);
        break;
    }
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
        bigThan2();
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

        MakeShadowMatrix(m_ground, lightpos, cubeXform);

        glMultMatrixf((GLfloat *)cubeXform);

        glTranslatef(-10.0f, 0.0f, 10.0f);
        // Set drawing color to Black
        glColor3f(0.0f, 0.0f, 0.0f);
        glutSolidCube(50.0f);
        break;
    }
        /*
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
    glOrtho(-100.0f, windowWidth, -100.0f, windowHeight, -90.0f, 90.0f);

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
      update();
      return QOpenGLWidget::keyPressEvent(event);
}

void OpenglWidget::drawPlate()
{
    glColor3f(0.0f, 0.0f, 0.90f); // Blue
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, -25.3f, -100.0f);
    glVertex3f(-100.0f, -25.3f, 100.0f);
    glVertex3f(100.0f,  -25.3f, 100.0f);
    glVertex3f(100.0f,  -25.3f, -100.0f);
    glEnd();
}

void OpenglWidget::bigThan2()
{
//    glEnable(GL_DEPTH_TEST); //! 开启深度测试
//    glDepthFunc(GL_LEQUAL); //! 指定深度缓冲比较值
    glEnable(GL_COLOR_MATERIAL);
    //! 设置环境光强度
    glLightfv(GL_LIGHT0, GL_AMBIENT, m_lightAmbient);
    //! 设置散色光
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, m_lightDiffuse);
    //! 设置镜面光
//    glLightfv(GL_LIGHT0, GL_SPECULAR, m_lightSpecular);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //! 设置材质
//    glMaterialfv(GL_FRONT, GL_SPECULAR,m_lightSpecular);
//    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_materialColor);
//    glMateriali(GL_FRONT, GL_SHININESS,128);
}
