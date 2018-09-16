#ifndef OPENGLUI_H
#define OPENGLUI_H
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QQuaternion>

class UnizModelData;

class OpenglUI : public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenglUI(QWidget *parent);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent *event)override;
    virtual void mousePressEvent(QMouseEvent *e)override;
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);




private:
    void drawAxis(float length);

    void drawRectRotateRectOrigin();

    void drawStairs();
    void drawOneLevel();
    void drawHandRail();


    void drawSolarSystem();
    void drawEarth();
    void drawMoon();

private:
    GLfloat zRotate;

    GLuint vertextVBO;
    GLuint vertextIBO;
};

#endif // OPENGLUI_H
