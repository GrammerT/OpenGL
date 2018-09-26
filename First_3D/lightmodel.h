#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QVector>
#include <QOpenGLShaderProgram>


class LightModel
{
public:
    LightModel();
    void initData();
    void draw(QOpenGLShaderProgram &shader);
private:
    typedef QVector<QVector3D> vec3D;
    typedef QVector<unsigned int> vecIndex;

    vec3D data;
    vecIndex indexs;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ebo;

    QOpenGLVertexArrayObject vao;
};


#endif // LIGHTMODEL_H
