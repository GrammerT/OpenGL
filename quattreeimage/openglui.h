#ifndef OPENGLUI_H
#define OPENGLUI_H

#include <QOpenGLWidget>
#include <QSharedPointer>
#include <QQuaternion>
#include <QVector2D>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "UnizWorldViewTray.h"

class UnizModelData;
class Box;

class OpenglUI : public QOpenGLWidget ,public QOpenGLFunctions
{
    Q_OBJECT
public:
    typedef QVector<QVector3D> Vec3Array;
    typedef QVector<QVector4D> Vec4Array;
    typedef QVector<unsigned int> IndexArray;
    OpenglUI(QWidget *parent);

    virtual void initializeGL();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

public slots:
    void onImageClick();
    void onCaptureImage();

private:
    void formTray();
    void formModelData(QSharedPointer<UnizModelData> data);
    void initShader();
    /**
     * @brief generatePoint
     * @param img : image
     * @param distance : two point min distance.
     * @param aspect : real distance and pixel aspect
     */
    void generatePoint(QImage &img, float distance, float aspect);
    QImage mergeTwoImage(QImage baseImage,QImage upImage);
    void capturePoint(QImage image, int distance_pixel, int tree_deep);
    QImage painterRectToImage(QImage image,QVector<QRect> &rects);
private:
    QOpenGLShaderProgram program;
    QOpenGLShaderProgram faceProgram;
    QSharedPointer<UnizModelData> data;
//    QSharedPointer<UnizWorldViewTray> tray;
    QVector2D _mousePressPosition;
    QQuaternion _rotation;
    QSharedPointer<Box> _box;
    QMatrix4x4 _projection;
    QMatrix4x4 _view;
    QMatrix4x4 _model;

    Vec4Array vColors;
    bool isFacePro;
};

#endif // OPENGLUI_H
