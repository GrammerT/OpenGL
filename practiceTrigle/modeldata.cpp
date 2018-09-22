#include "modeldata.h"
#include <QOpenGLFunctions>
ModelData::ModelData()
{
    data.push_back(QVector3D(-0.5,-0.5,0.0));
    data.push_back(QVector3D(0.5,-0.5,0.0));
    data.push_back(QVector3D(0.5,0.5,0.0));
    data.push_back(QVector3D(-0.5,0.5,0.0));

    indexs.push_back(0);
    indexs.push_back(1);
    indexs.push_back(2);

    indexs.push_back(2);
    indexs.push_back(3);
    indexs.push_back(0);


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

    ebo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ebo.create();
    ebo.bind();
    ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ebo.allocate(indexs.constData(),indexs.count()*sizeof(unsigned int));

}

void ModelData::draw(QOpenGLShaderProgram &shader)
{
//    QOpenGLVertexArrayObject::Binder vaoBinder(&vao);
    // If VAOs are not supported, set the vertex attributes every time.
//    if (vao.isCreated())
//    {

//    }
//    else
    {
        int pos = shader.attributeLocation("aPos");
        shader.enableAttributeArray(pos);
        shader.setAttributeBuffer(pos,GL_FLOAT,0,3,sizeof(QVector3D));
//        shader.setAttributeBuffer(pos,GL_UNSIGNED_INT,0,3,0);
    }
//    glDrawArrays(GL_TRIANGLES,0,data.count());
    glDrawElements(GL_TRIANGLES,indexs.count(),GL_UNSIGNED_INT,0);
}
