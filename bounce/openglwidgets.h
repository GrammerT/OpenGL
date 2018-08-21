#ifndef OPENGLWIDGETS_H
#define OPENGLWIDGETS_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>


class OpenGLWidgets:public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWidgets(QWidget *parent = 0);
protected:

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent *event)override;
public slots:
    void onTimerout();
private:
    GLfloat point_x;
    GLfloat point_y;
    GLfloat rectSize;
    // Step size in x and y directions
    // (number of pixels to move each time)
    GLfloat xstep ;
    GLfloat ystep ;

    // Keep track of windows changing width and height
    GLfloat windowWidth;
    GLfloat windowHeight;

};

#endif // OPENGLWIDGETS_H
