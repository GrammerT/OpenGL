#ifndef OPENGGLWIDGET_H
#define OPENGGLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QVector4D>
#include <QVector3D>

class OpengGLWidget :public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpengGLWidget(QWidget *parent = 0);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent *event)override;
private:
    QVector4D lightPos;
    QVector4D specular;
    QVector4D specref;
    QVector4D ambientLight;
    QVector3D spotDir;

    GLfloat xRot;
    GLfloat yRot;


};

#endif // OPENGGLWIDGET_H
