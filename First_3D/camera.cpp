#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::setCamera(QVector3D eye, QVector3D center, QVector3D up)
{

    this->eye = eye;
    this->look = center;
    this->up = up;
//    QVector3D upvec = up-eye;
    //! 摄像机坐标系统
//    cameraDirection=eye-look;
//    cameraRight = QVector3D::crossProduct(this->up,cameraDirection);
//    cameraUp=QVector3D::crossProduct(cameraDirection,cameraRight);

//    cameraDirection.normalize();
//    cameraRight.normalize();
//    cameraUp.normalize();
    setModelViewMatrix();
}

void Camera::roll(float angle)
{

    float cs=cos(angle*3.14159265/180);
    float sn=sin(angle*3.14159265/180);
//    Vector3 t(u);
//    Vector3 s(v);
//    u.set(cs*t.x-sn*s.x, cs*t.y-sn*s.y, cs*t.z-sn*s.z);
//    v.set(sn*t.x+cs*s.x, sn*t.y+cs*s.y, sn*t.z+cs*s.z);
//    setModelViewMatrix();
}

void Camera::pitch(float angle)
{

    float cs=cos(angle*3.14159265/180);
    float sn=sin(angle*3.14159265/180);
//    Vector3 t(v);
//    Vector3 s(n);
//    v.set(cs*t.x-sn*s.x, cs*t.y-sn*s.y, cs*t.z-sn*s.z);
//    n.set(sn*t.x+cs*s.x, sn*t.y+cs*s.y, sn*t.z+cs*s.z);
//    setModelViewMatrix();
}

void Camera::yaw(float angle)
{

    float cs=cos(angle*3.14159265/180);
    float sn=sin(angle*3.14159265/180);
//    Vector3 t(n);
//    Vector3 s(u);
//    n.set(cs*t.x-sn*s.x, cs*t.y-sn*s.y, cs*t.z-sn*s.z);
//    u.set(sn*t.x+cs*s.x, sn*t.y+cs*s.y, sn*t.z+cs*s.z);
//    setModelViewMatrix();
}

void Camera::slide(float du, float dv, float dn)
{

//    eye.x+=du*u.x+dv*v.x+dn*n.x;
//    eye.y+=du*u.y+dv*v.y+dn*n.y;
//    eye.z+=du*u.z+dv*v.z+dn*n.z;
//    look.x+=du*u.x+dv*v.x+dn*n.x;
//    look.y+=du*u.y+dv*v.y+dn*n.y;
//    look.z+=du*u.z+dv*v.z+dn*n.z;
//    setModelViewMatrix();
}

float Camera::getDist()
{
//    float dist=pow(eye.x,2)+pow(eye.y,2)+pow(eye.z,2);
//        return pow(dist,0.5);
    return 0;
}

void Camera::setShape(float viewAngle, float aspect, float Near, float Far)
{

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(viewAngle,aspect, Near, Far);

}

void Camera::setModelViewMatrix()
{
    float m[16];
    QVector3D eVec=eye;
////    m[0]=u.x; m[4]=u.y; m[8]=u.z; m[12]=-eVec.dot(u);
////    m[1]=v.x; m[5]=v.y; m[9]=v.z; m[13]=-eVec.dot(v);
////    m[2]=n.x; m[6]=n.y; m[10]=n.z; m[14]=-eVec.dot(n);
////    m[3]=0;  m[7]=0;  m[11]=0;  m[15]=1.0;
////    glMatrixMode(GL_MODELVIEW);
////    glLoadMatrixf(m);
}
