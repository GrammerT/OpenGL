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
    ,zTrans(-100.0)
{
    m_data = new UnizModelData;
//    FormGraphics::formCircle(m_data,QVector3D(0,0,0),40.0);
    FormGraphics::formRoundTable(m_data,QVector3D(0,0,5),1.2,QVector3D(0,0,-5),4.0);

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
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, 20.0f), QVector3D(0.0f,0.0f,1.0f), QVector3D(0.0f,1.0f,0.0f));
    qDebug()<<view;


    /**
        1.材料反射率都为0，则物体显示黑色
        2.漫反射有值，其余为0，则漫反射可以控制物体颜色
        3.只有镜面反射，其他为0，则对应的面会显示颜色
        4.
    */
    program.setUniformValue("Material.RateAmbient", 0.9f, 0.5f, 0.3f);
    program.setUniformValue("Material.RateDiffuse", 0.9f, 0.5f, 0.3f);
    program.setUniformValue("Material.RateSpecular", 0.8f, 0.8f, 0.8f);
    program.setUniformValue("Material.Shininess", 100.0f);

    program.setUniformValue("Light.LightAmbient", 0.4f, 0.4f, 0.4f);
    program.setUniformValue("Light.LightDiffuse", 1.0f, 1.0f, 1.0f);
    program.setUniformValue("Light.LightSpecular", 1.0f, 1.0f, 1.0f);

    QVector4D worldLight = QVector4D(0.0f,0.0f,20.0f,1.0f);
    program.setUniformValue("Light.Position", view * worldLight );
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.translate(0.0, 0.0, zTrans);
    matrix.rotate(rotation);
    QMatrix4x4 MVP = projection*view*matrix;
    program.setUniformValue("ModelViewMatrix", view*matrix);
    program.setUniformValue("MVP", MVP);
    program.setUniformValue("ProjectionMatrix", projection);
    program.setUniformValue("NormalMatrix", (view*matrix).normalMatrix());
    program.bind();
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
    const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();
    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
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

void OpenglUI::wheelEvent(QWheelEvent *event)
{
    QPoint p = event->angleDelta()/5.0;
    if(p.y()<0)
    {
        zTrans -= 0.75f;
    }
    else
    {
        zTrans += 0.75f;
    }
    this->update();

}

void OpenglUI::initShader()
{

//    // vertex shader
//    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
//    vshader->compileSourceFile(":/function.vert");
//    // fragment shader
//    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
//    fshader->compileSourceFile(":/function.frag");
    // Compile vertex shader
//    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
//        close();
//    // Compile fragment shader
//    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
//        close();

    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/function.vert"))
        close();
    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/function.frag"))
        close();
    // Link shader pipeline
    if (!program.link())
        close();
    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
