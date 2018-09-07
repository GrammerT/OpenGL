#ifndef UNIZGENNORMALFUNCTOR_H
#define UNIZGENNORMALFUNCTOR_H

#include <QVector3D>
#include <QVector>

struct UnizGenNormalFunctor
{
    UnizGenNormalFunctor()
        : _normals(NULL)
    {}

    typedef QVector<QVector3D> Vec3Array;

    Vec3Array *_normals;

    void set(Vec3Array *normals)
    {
        _normals = normals;
    }

    void reset()
    {
        _normals = NULL;
    }

    inline void operator()(const QVector3D &v1, const QVector3D &v2, const QVector3D& v3)
    {
        QVector3D normal = QVector3D::crossProduct(v2 - v1, v3 - v1);
//        QVector3D normal = QVector3D::crossProduct(v2 - v1, v3 - v1);

        normal.normalize();

        _normals->push_back(normal);
        _normals->push_back(normal);
        _normals->push_back(normal);
    }
};

#endif // UNIZGENNORMALFUNCTOR_H
