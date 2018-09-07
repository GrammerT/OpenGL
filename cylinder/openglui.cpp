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
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    initShader();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);
    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, -30.0f), QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,1.0f,0.0f));
//    program.setUniformValue("Kd", QVector3D(0.9f, 0.5f, 0.3f));
    program.setUniformValue("Kd", QVector3D(0.0f, 1.0f, 0.0f));

    program.setUniformValue("Ld", QVector3D(1.0f, 1.0f, 1.0f));
    program.setUniformValue("LightPosition", view * QVector4D(25.0f,0.0f,0.0f,1.0f));
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    static int i=20;
    matrix.translate(0.0, 0.0, i--);
//    matrix.rotate(rotation);

    program.setUniformValue("m_matrix", matrix);
    program.setUniformValue("v_matrix", view);
    program.setUniformValue("p_matrix", projection);
    program.setUniformValue("n_matrix", (view*matrix).normalMatrix());

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

void OpenglUI::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        QVector2D newPos = (QVector2D)event->pos();
        QVector2D diff = newPos - mousePressPosition;
        qreal angle = (diff.length())/3.6;
        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
        mousePressPosition = newPos;
        this->update();
    }
    event->accept();
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
