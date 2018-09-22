#include "modeldata.h"
#include <QOpenGLFunctions>
ModelData::ModelData()
{
    data.push_back(QVector3D(-0.5,-0.5,0.0));
    data.push_back(QVector3D(0.5,-0.5,0.0));
    data.push_back(QVector3D(0.0,0.5,0.0));
    initData();
}

ModelData::~ModelData()
{
    vbo.destroy();
}

void ModelData::initData()
{
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    qDebug()<<data.count()*sizeof(QVector3D);
    qDebug()<<sizeof(GL_FLOAT);
    vbo.allocate(data.constData(),data.count()*sizeof(QVector3D));
}

void ModelData::draw(QOpenGLShaderProgram &shader)
{
    int pos = shader.attributeLocation("aPos");
    shader.enableAttributeArray(pos);
    shader.setAttributeBuffer(pos,GL_FLOAT,0,3,sizeof(QVector3D));
    glDrawArrays(GL_TRIANGLES,0,sizeof(QVector3D));
}
