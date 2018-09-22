#ifndef OPENGLUI_H
#define OPENGLUI_H
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "modeldata.h"

class OpenglUI : public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenglUI(QWidget *parent = 0);

    virtual void initializeGL();
    virtual void resizeGL(int w,int h);
    virtual void paintGL();

private:
    void initShader();

private:
    QOpenGLShaderProgram shaderProcess;
    ModelData *md;
};

#endif // OPENGLUI_H
