#ifndef MODELDATA_H
#define MODELDATA_H
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QVector>
#include <QOpenGLShaderProgram>

class ModelData
{
public:
    ModelData();
    ~ModelData();
    void initData();
    void draw(QOpenGLShaderProgram &shader);
private:
    typedef QVector<QVector3D> vec3D;
    vec3D data;
    typedef QVector<unsigned int> vecIndex;
    vecIndex indexs;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ebo;
    QOpenGLVertexArrayObject vao;
};

#endif // MODELDATA_H
