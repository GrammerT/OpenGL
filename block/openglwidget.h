#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector4D>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

class OpenglWidget: public QOpenGLWidget,protected QOpenGLFunctions
{
public:
    OpenglWidget(QWidget *parent=0);

    void initPoints();
    void initShader();

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent *event)override;

private:
    void drawPlate();
    void bigThan2();
private:
    GLfloat m_lightPos[4];
    GLfloat m_lightAmbient[4] ;
    GLfloat m_lightDiffuse[3];
    GLfloat m_lightSpecular[3];
    GLfloat m_materialColor[3];
    QVector<GLfloat> m_ground;
    GLfloat m_textures[4];
    int m_Step;
    QVector<QVector3D> m_points;

    QOpenGLShaderProgram m_program;
    QOpenGLBuffer m_plateArrayBuf;
    QOpenGLBuffer m_plateIndexBuf;


    QOpenGLBuffer m_arrayBuf;
    QOpenGLBuffer m_indexBuf;
    // Lighting data
    QMatrix4x4 m_matrix;

};

#endif // OPENGLWIDGET_H
