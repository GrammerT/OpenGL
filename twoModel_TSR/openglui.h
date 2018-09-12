#ifndef OPENGLUI_H
#define OPENGLUI_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

class OpenglUI:public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenglUI(QWidget *parent = 0);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
private:
    QMatrix4x4 projection;
    QMatrix4x4 view;

};

#endif // OPENGLUI_H
