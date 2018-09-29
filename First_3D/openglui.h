#ifndef OPENGLUI_H
#define OPENGLUI_H
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "modeldata.h"
#include "lightmodel.h"
#include <QMatrix4x4>
#include <QVector2D>
#include <QQuaternion>
#include "camera.h"

typedef struct view_info
{
public:
    QVector3D eye;
    QVector3D center;
    QVector3D up;
}ViewInfo;


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

    virtual void keyPressEvent(QKeyEvent *event);

private:
    void initShader();
    void initMatrix(int w, int h);

private:
    QMatrix4x4 project;
    QMatrix4x4 view;

    QQuaternion ModelRotation;
    QQuaternion viewRotation;
    ViewInfo viewInfo;
    Camera m_Camera;
    QVector2D mousePressPosition;
    QOpenGLShaderProgram shaderProcess;
    QOpenGLShaderProgram lightShaderProcess;
    ModelData *md;
    LightModel *lightData;
    typedef QVector<QVector3D> vec3D;
    vec3D modelsCount;
};

#endif // OPENGLUI_H
