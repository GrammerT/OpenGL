#ifndef UNIZWORLDVIEWTRAY_H
#define UNIZWORLDVIEWTRAY_H

#include <QVector3D>
#include <QVector>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class UnizWorldViewTray : private QOpenGLFunctions
{
    typedef QVector<QVector3D> Vec3Array;
public:
    UnizWorldViewTray();
    ~UnizWorldViewTray();

    UnizWorldViewTray& setTrayInterval(float trayInterval);
    UnizWorldViewTray& setMarginX(float marginX);
    UnizWorldViewTray& setMarginY(float marginY);
    UnizWorldViewTray& setBuildArea(const QVector3D &buildArea);

    bool build();

    void reset();

    QMatrix4x4 getTrayMatrix() const;

    void draw(QOpenGLShaderProgram *program);
    void render(QOpenGLShaderProgram &program);

private:
    bool canBuild();
    void resetFenceCollision();

    float mTrayInterval;
    float mMarginX;
    float mMarginY;
    QVector3D mBuildArea;

    Vec3Array mVertexArray;

    QOpenGLBuffer mArrayBuffer;

    unsigned int mThickLineStart;
    unsigned int mFaceIndexStart;

    bool mDirty;
    bool mFenceCollision[6];
};

#endif // UNIZWORLDVIEWTRAY_H
