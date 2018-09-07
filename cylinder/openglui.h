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
    virtual void mouseReleaseEvent(QMouseEvent *e)override;
public slots:
    void onTimerout();
private:
//    void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N);
    void initShader();
private:
    QOpenGLShaderProgram program;
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QQuaternion rotation;
    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    UnizModelData *m_data;
    GLfloat xRot;
    GLfloat yRot;
};

#endif // OPENGLUI_H
