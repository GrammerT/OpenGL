#include "openglui.h"
#include <QDebug>
#include <QMouseEvent>
#include <QtMath>


OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
{
    this->setFocusPolicy(Qt::StrongFocus);
    modelsCount.push_back(QVector3D(0.0f,  0.0f,  0.0f));
    modelsCount.push_back(QVector3D(2.0f,  5.0f, -15.0f));
    modelsCount.push_back(QVector3D(-1.5f, -2.2f, -2.5f));
    modelsCount.push_back(QVector3D(-3.8f, -2.0f, -12.3f));
    modelsCount.push_back(QVector3D(2.4f, -0.4f, -3.5f));
    modelsCount.push_back(QVector3D(-1.7f,  3.0f, -7.5f));
    modelsCount.push_back(QVector3D(1.3f, -2.0f, -2.5f));
    modelsCount.push_back(QVector3D(1.5f,  2.0f, -2.5f));
    modelsCount.push_back(QVector3D(1.5f,  0.2f, -1.5f));
    modelsCount.push_back(QVector3D(-1.3f,  1.0f, -1.5f));
    viewInfo.eye = QVector3D(0.0,0.0,3.0);
    viewInfo.center = QVector3D(0.0,0.0,0.0);
    viewInfo.up = QVector3D(0.0,1.0,0.0);

    qDebug()<<qSin(M_PI/6); //30
    qDebug()<<qCos(M_PI/3); //60

}

void OpenglUI::initializeGL()
{
    initializeOpenGLFunctions();
    initShader();
    md = new ModelData;
    glClearColor(1.0,0.0,0.0,1.0);

}

void OpenglUI::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    initMatrix(w,h);
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    qDebug()<< shaderProcess.bind();

    for(int i=0;i<modelsCount.size();++i)
    {
        QMatrix4x4 model;
        if(i%3==0)
        {
            model.rotate(ModelRotation);
        }
        model.translate(modelsCount[i]);
        int mat = shaderProcess.uniformLocation("ModelViewProjectionMatrix");
        shaderProcess.enableAttributeArray(mat);
        shaderProcess.setUniformValue(mat,project*view*model);
        md->draw(shaderProcess);
    }
}

void OpenglUI::mousePressEvent(QMouseEvent *event)
{
    mousePressPosition = (QVector2D)event->pos();
}

void OpenglUI::mouseMoveEvent(QMouseEvent *event)
{
    QVector2D newPos = (QVector2D)event->pos();
    QVector2D diff = newPos - mousePressPosition;
    if(event->buttons() == Qt::LeftButton)
    {
        qreal angle = (diff.length())/3.5;
        // ModelRotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D ModelRotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        ModelRotation = QQuaternion::fromAxisAndAngle(ModelRotationAxis, angle) * ModelRotation;
    }
    else
    {
        qreal angle = (diff.length())/10.5;
        QVector3D ModelRotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        viewRotation = QQuaternion::fromAxisAndAngle(ModelRotationAxis, angle);
//        view.rotate(viewRotation);
        float radius = 10.0f;
        static float i = 360.0;
        float z = qSin(2*M_PI/i) * radius;
        float x = qCos(2*M_PI/i)*radius;
        i-=0.01;
        if(i<1)
            i=360.0;
        viewInfo.eye = QVector3D(x,0.0,z);
        view.lookAt(viewInfo.eye,viewInfo.center,viewInfo.up);
    }
    mousePressPosition = newPos;
    this->update();
    event->accept();
}

void OpenglUI::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        view.translate(0.0,0.0,2.0);
        break;
    case Qt::Key_S:
        view.translate(0.0,0.0,-2.0);
        break;
    case Qt::Key_D:
        view.translate(2.0,0.0,0.0);
        break;
    case Qt::Key_A:
        view.translate(-2.0,0.0,0.0);
        break;
    default:
        break;
    }
    this->update();
}


void OpenglUI::initShader()
{
    qDebug()<< shaderProcess.create();
    shaderProcess.addShaderFromSourceFile(QOpenGLShader::Vertex,":/vertex.vert");
    shaderProcess.addShaderFromSourceFile(QOpenGLShader::Fragment,":/fragment.frag");
    qDebug()<<shaderProcess.link();
    shaderProcess.bind();
}

void OpenglUI::initMatrix(int w,int h)
{
    view.setToIdentity();
    project.setToIdentity();
    float as =0.0;
    if(w>h)
    {
        as = (GLfloat)w/(GLfloat)h;
    }
    else
    {
        as = (GLfloat)h/(GLfloat)w;
    }
    view.lookAt(viewInfo.eye,viewInfo.center,viewInfo.up);
    project.perspective(45.0,as,0.1,100.0);
}
