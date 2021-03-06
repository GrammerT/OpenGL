#include "openglwidget.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QWheelEvent>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
    ,xtrans(0),ytrans(0),ztrans(0.0)
{

}

OpenGLWidget::~OpenGLWidget()
{
    delete torus;
    delete program;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // vertex shader
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vshader->compileSourceFile(":/shader/diffuse.vert");
    // fragment shader
    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fshader->compileSourceFile(":/shader/diffuse.frag");

    // shader program
    program = new QOpenGLShaderProgram;
    program->addShader(vshader);
    program->addShader(fshader);

    program->link();
    program->bind();

    // set color used to clear background
    glClearColor(0.5f, 0.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // vertices array
    torus = new VBOTorus(0.7f, 0.3f, 30, 30);

    // view matrix
    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, 3.0f), QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,1.0f,0.0f));

    // uniform light/material property
    program->setUniformValue("Kd", QVector3D(1.0f, 1.0f, 0.3f));
    program->setUniformValue("Ld", QVector3D(1.0f, 1.0f, 1.0f));
    program->setUniformValue("LightPosition", view * QVector4D(0.0f,0.0f,5.0f,1.0f) );
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w/2,h/2);
    projection.setToIdentity();
    projection.perspective(60.0f, (GLfloat)w/(GLfloat)h, 0.001f, 100.0f);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // transform the model
    model.setToIdentity();
    model.translate(xtrans, ytrans, ztrans);
    model.rotate(rotation);
    QMatrix4x4 mv = view * model;
    program->setUniformValue("ModelViewMatrix", mv);
    program->setUniformValue("NormalMatrix",
                             mv.normalMatrix());
    program->setUniformValue("MVP", projection * mv);

    program->bind();
    // render the object
    torus->render();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    mousePos = QVector2D(event->pos());
    event->accept();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    QVector2D newPos = (QVector2D)event->pos();
    QVector2D diff = newPos - mousePos;
    if(event->buttons() == Qt::LeftButton)
    {
        qreal angle = (diff.length())/3.6;
        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
        mousePos = newPos;
        this->update();
    }
    else
    {
        mousePos = newPos;

        this->update();
    }
    event->accept();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    if (numDegrees.y() > 0) {
        ztrans += 0.25f;
    } else if (numDegrees.y() < 0) {
        ztrans -= 0.25f;
    }
    this->update();
    event->accept();
}
