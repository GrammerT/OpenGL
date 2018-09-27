#include "modeldata.h"
#include <QOpenGLFunctions>
ModelData::ModelData()
{
    data.push_back(QVector3D(-0.5,-0.5,0.5));
    data.push_back(QVector3D(0.5,-0.5,0.5));
    data.push_back(QVector3D(0.5,0.5,0.5));
    data.push_back(QVector3D(-0.5,0.5,0.5));

    data.push_back(QVector3D(-0.5,-0.5,-0.5));
    data.push_back(QVector3D(0.5,-0.5,-0.5));
    data.push_back(QVector3D(0.5,0.5,-0.5));
    data.push_back(QVector3D(-0.5,0.5,-0.5));

    normal.push_back(QVector3D(0.0,0.0,1.0));
    normal.push_back(QVector3D(0.0,0.0,1.0));
    normal.push_back(QVector3D(0.0,0.0,1.0));
    normal.push_back(QVector3D(0.0,0.0,1.0));
    normal.push_back(QVector3D(0.0,0.0,1.0));
    normal.push_back(QVector3D(0.0,0.0,1.0));
    indexs.push_back(0);
    indexs.push_back(1);
    indexs.push_back(2);
    indexs.push_back(2);
    indexs.push_back(3);
    indexs.push_back(0);

    normal.push_back(QVector3D(0.0,-1.0,0.0));
    normal.push_back(QVector3D(0.0,-1.0,0.0));
    normal.push_back(QVector3D(0.0,-1.0,0.0));
    normal.push_back(QVector3D(0.0,-1.0,0.0));
    normal.push_back(QVector3D(0.0,-1.0,0.0));
    normal.push_back(QVector3D(0.0,-1.0,0.0));
    indexs.push_back(0);
    indexs.push_back(4);
    indexs.push_back(1);
    indexs.push_back(1);
    indexs.push_back(4);
    indexs.push_back(5);


    normal.push_back(QVector3D(0.0,0.0,-1.0));
    normal.push_back(QVector3D(0.0,0.0,-1.0));
    normal.push_back(QVector3D(0.0,0.0,-1.0));
    normal.push_back(QVector3D(0.0,0.0,-1.0));
    normal.push_back(QVector3D(0.0,0.0,-1.0));
    normal.push_back(QVector3D(0.0,0.0,-1.0));
    indexs.push_back(4);
    indexs.push_back(7);
    indexs.push_back(6);
    indexs.push_back(4);
    indexs.push_back(6);
    indexs.push_back(5);

    normal.push_back(QVector3D(0.0,1.0,0.0));
    normal.push_back(QVector3D(0.0,1.0,0.0));
    normal.push_back(QVector3D(0.0,1.0,0.0));
    normal.push_back(QVector3D(0.0,1.0,0.0));
    normal.push_back(QVector3D(0.0,1.0,0.0));
    normal.push_back(QVector3D(0.0,1.0,0.0));
    indexs.push_back(3);
    indexs.push_back(2);
    indexs.push_back(6);
    indexs.push_back(3);
    indexs.push_back(6);
    indexs.push_back(7);

    normal.push_back(QVector3D(-1.0,0.0,0.0));
    normal.push_back(QVector3D(-1.0,0.0,0.0));
    normal.push_back(QVector3D(-1.0,0.0,0.0));
    normal.push_back(QVector3D(-1.0,0.0,0.0));
    normal.push_back(QVector3D(-1.0,0.0,0.0));
    normal.push_back(QVector3D(-1.0,0.0,0.0));
    indexs.push_back(0);
    indexs.push_back(3);
    indexs.push_back(4);
    indexs.push_back(4);
    indexs.push_back(3);
    indexs.push_back(7);

    normal.push_back(QVector3D(1.0,0.0,0.0));
    normal.push_back(QVector3D(1.0,0.0,0.0));
    normal.push_back(QVector3D(1.0,0.0,0.0));
    normal.push_back(QVector3D(1.0,0.0,0.0));
    normal.push_back(QVector3D(1.0,0.0,0.0));
    normal.push_back(QVector3D(1.0,0.0,0.0));
    indexs.push_back(1);
    indexs.push_back(5);
    indexs.push_back(2);
    indexs.push_back(2);
    indexs.push_back(5);
    indexs.push_back(6);

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

    normalBuffer.create();
    normalBuffer.bind();
    normalBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    normalBuffer.allocate(normal.constData(),sizeof(QVector3D)*normal.count());

    ebo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ebo.create();
    ebo.bind();
    ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ebo.allocate(indexs.constData(),indexs.count()*sizeof(unsigned int));

}

void ModelData::draw(QOpenGLShaderProgram &shader)
{
    ebo.bind();
    {
        int objectColor = shader.uniformLocation("objectColor");
        shader.enableAttributeArray(objectColor);
        shader.setUniformValue(objectColor,QVector3D(1.0f, 0.5f, 0.31f));

        vbo.bind();
        int pos = shader.attributeLocation("Vertex");
        shader.enableAttributeArray(pos);
        shader.setAttributeBuffer(pos,GL_FLOAT,0,3,sizeof(QVector3D));

        normalBuffer.bind();
        int norm = shader.attributeLocation("normal");
        shader.enableAttributeArray(norm);
        shader.setAttributeBuffer(norm,GL_FLOAT,0,3,sizeof(QVector3D));
    }
    glDrawElements(GL_TRIANGLES,indexs.count(),GL_UNSIGNED_INT,0);
}
