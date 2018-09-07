#include "openglui.h"
#include "UnizModeldata.h"
#include <QDebug>
#include <QtMath>
#include <QKeyEvent>
#include <QTimer>
#include "formgraphics.h"

OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
    ,angularSpeed(0)
{
    m_data = new UnizModelData;
    FormGraphics::formCircle(m_data,QVector3D(0,0,0),40);
    this->setFocusPolicy(Qt::StrongFocus);
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerout()));
//    timer->start(100);
//    rotation.setScalar(1.0);
}

void OpenglUI::onTimerout()
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01)
    {
        angularSpeed = 0.0;
    }
    else
    {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        // Request an update
        update();
    }
}

void OpenglUI::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    initShader();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//    glEnable(GL_LIGHTING);
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    program.setUniformValue("lightColor", QVector3D(1.0,1.0,1.0));
    program.setUniformValue("lightPos",QVector3D(0.0,0.0,40.0));
    program.setUniformValue("objColor",QVector3D(0.0,1.0,0.0));
    program.setUniformValue("eyePos",QVector3D(0.0,0.0,35.0));


    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -200);
    matrix.rotate(rotation);
    program.setUniformValue("m_matrix", matrix);
    program.setUniformValue("v_matrix", view);
    program.setUniformValue("p_matrix", projection);
    if(m_data)
    {
        m_data->draw(program);
    }
}

void OpenglUI::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 10000.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();
    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);

    view.setToIdentity();
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

void OpenglUI::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void OpenglUI::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01)
    {
        angularSpeed = 0.0;
    } else
    {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        // Request an update
        update();
    }
}

void OpenglUI::initShader()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

//球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份
//void OpenglUI::drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
//{
//    float step_z = M_PI/M;
//    float step_xy = 2*M_PI/N;
//    float x[4],y[4],z[4];

//    float angle_z = 0.0;
//    float angle_xy = 0.0;
//    int i=0, j=0;
//    static int r=0;
//    static int g=0;
//    static int b=0;
//    glBegin(GL_TRIANGLES);
//    for(i=0; i<M; i++)
//    {
//        angle_z = i * step_z;
//        for(j=0; j<N; j++)
//        {
//            angle_xy = j * step_xy;
//            x[0] = radius * sin(angle_z) * cos(angle_xy);
//            y[0] = radius * sin(angle_z) * sin(angle_xy);
//            z[0] = radius * cos(angle_z);

//            x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
//            y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
//            z[1] = radius * cos(angle_z + step_z);

//            x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);
//            y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);
//            z[2] = radius*cos(angle_z + step_z);

//            x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
//            y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
//            z[3] = radius * cos(angle_z);


//            if(r<255)
//            {
//                r++;
//                if(g<255)
//                {
//                    g++;
//                    if(b<255)
//                    {
//                        b++;
//                    }
//                    else
//                    {
//                        b=0;
//                    }
//                }
//                else
//                {
//                    g=0;
//                }
//            }
//            else
//            {
//                r = 0;
//            }
//            glColor3f((GLfloat)r/255.0,(GLfloat)g/255.0,(GLfloat)b/255.0);
//            for(int k=0; k<3; k++)
//            {
//                glVertex3f(xx+x[k], yy+y[k],zz+z[k]);
//            }
//            glColor3f(0.0f,1.0f,0.0f);
//            glVertex3f(xx+x[0], yy+y[0],zz+z[0]);
//            glVertex3f(xx+x[2], yy+y[2],zz+z[2]);
//            glVertex3f(xx+x[3], yy+y[3],zz+z[3]);
//        }
//    }
//    glEnd();
//    r = 0;
//    g = 0;
//    b = 0;
//}
