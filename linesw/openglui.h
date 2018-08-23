#ifndef OPENGLUI_H
#define OPENGLUI_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenglUI :public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenglUI(QWidget *parent = 0);
protected:

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w,int h);
    virtual void keyPressEvent(QKeyEvent *event);
private:
    GLfloat xRot;
    GLfloat yRot;
};

#endif // OPENGLUI_H
