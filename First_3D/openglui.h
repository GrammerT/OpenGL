#ifndef OPENGLUI_H
#define OPENGLUI_H
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "modeldata.h"
#include <QMatrix4x4>
#include <QVector2D>
#include <QQuaternion>

class OpenglUI : public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenglUI(QWidget *parent = 0);

    virtual void initializeGL();
    virtual void resizeGL(int w,int h);
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent *event)override;
    virtual void mouseMoveEvent(QMouseEvent *event)override;

private:
    void initShader();
    void initMatrix(int w, int h);

private:
    QMatrix4x4 project;
    QMatrix4x4 view;

    QQuaternion ModelRotation;
    QQuaternion viewRotation;
    QVector2D mousePressPosition;
    QOpenGLShaderProgram shaderProcess;
    ModelData *md;
    typedef QVector<QVector3D> vec3D;
    vec3D modelsCount;
};

#endif // OPENGLUI_H
