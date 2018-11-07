#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>


class Camera
{
public:
    /* 构造函数和析构函数 */
    Camera();
    ~Camera();

    /* 设置摄像机的位置, 观察点和向上向量 */
    void setCamera(QVector3D eye, QVector3D center, QVector3D up);
    void roll(float angle);
    void pitch(float angle);
    void yaw(float angle);
    void slide(float du, float dv, float dn);
    float getDist();
    void setShape(float viewAngle,float aspect,float Near,float Far);
private:

    void setModelViewMatrix();

private:
    /* 摄像机属性 */
    QVector3D   eye,look,up;
    QVector3D   u,v,n;
    float          viewAngle, aspect, nearDist, farDist;

};

#endif // CAMERA_H
