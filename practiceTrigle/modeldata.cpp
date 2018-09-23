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

    {
        int pos = shader.attributeLocation("aPos");
        shader.enableAttributeArray(pos);
        shader.setAttributeBuffer(pos,GL_FLOAT,0,3,sizeof(QVector3D));
        int color = shader.uniformLocation("color");
        shader.enableAttributeArray(color);
        shader.setUniformValue(color,QVector4D(0.9,0.1,0.1,1.0));

    }

    QMatrix4x4 mat1;
    static int rotate=0;
    mat1.translate(0.5,0.5,0.0);
    mat1.rotate(rotate++,0.0,0.0,1.0);
    int modelMat= shader.uniformLocation("modelMat");
    shader.enableAttributeArray(modelMat);
    shader.setUniformValue(modelMat,mat1);
    glDrawElements(GL_TRIANGLES,indexs.count(),GL_UNSIGNED_INT,0);
    QMatrix4x4 mat2;
    mat2.translate(-0.5,0.5,0.0);
    mat2.rotate(rotate+=3,0.0,0.0,1.0);
    int modelMat1= shader.uniformLocation("modelMat");
    shader.enableAttributeArray(modelMat1);
    shader.setUniformValue(modelMat1,mat2);
    glDrawElements(GL_TRIANGLES,indexs.count(),GL_UNSIGNED_INT,0);
}
