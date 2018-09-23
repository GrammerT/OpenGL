#include "openglui.h"
#include <QDebug>
#include <QMouseEvent>


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
    if(event->buttons() == Qt::LeftButton)
    {
        QVector2D newPos = (QVector2D)event->pos();
        QVector2D diff = newPos - mousePressPosition;
        qreal angle = (diff.length())/3.5;
        // ModelRotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D ModelRotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        ModelRotation = QQuaternion::fromAxisAndAngle(ModelRotationAxis, angle) * ModelRotation;
        mousePressPosition = newPos;
        this->update();
    }
    else
    {
        QVector2D newPos = (QVector2D)event->pos();
        QVector2D diff = newPos - mousePressPosition;
        qreal angle = (diff.length())/10.5;
        QVector3D ModelRotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        viewRotation = QQuaternion::fromAxisAndAngle(ModelRotationAxis, angle);
        view.rotate(viewRotation);
        mousePressPosition = newPos;
        this->update();
    }
    event->accept();
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
//    view.translate(0.0,0.0,-3.0);
    view.lookAt(QVector3D(0.0,0.0,3.0),QVector3D(0.0,0.0,0.0),QVector3D(0.0,1.0,0.0));
    project.perspective(45.0,as,0.1,100.0);
}
