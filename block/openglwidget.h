#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector4D>
#include <QVector3D>

class OpenglWidget: public QOpenGLWidget,protected QOpenGLFunctions
{
public:
    OpenglWidget(QWidget *parent=0);
    virtual void initializeOpenGLFunctions();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent *event);
private:
    GLfloat m_lightPos[4];
    GLfloat m_lightAmbient[4] ;
    GLfloat m_lightDiffuse[3];
    GLfloat m_lightSpecular[3];
    GLfloat m_materialColor[3];
    QVector<GLfloat> m_ground;
    GLfloat m_textures[4];
    int m_Step;
    // Lighting data

};

#endif // OPENGLWIDGET_H
