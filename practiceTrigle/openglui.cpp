#include "openglui.h"
#include <QDebug>

OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
{
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
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    qDebug()<< shaderProcess.bind();
    md->draw(shaderProcess);
}

void OpenglUI::initShader()
{
    qDebug()<< shaderProcess.create();
    shaderProcess.addShaderFromSourceFile(QOpenGLShader::Vertex,":/vertex.vert");
    shaderProcess.addShaderFromSourceFile(QOpenGLShader::Fragment,":/fragment.frag");
    qDebug()<<shaderProcess.link();
    shaderProcess.bind();
}
