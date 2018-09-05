#ifndef UNIZCOMPAREFUCTOR_H
#define UNIZCOMPAREFUCTOR_H

#include <QVector3D>

struct QVector3DCompare
{
    bool operator()(const QVector3D &lhs, const QVector3D &rhs) const
    {
        if (lhs.z() < rhs.z())
            return true;
        else if (lhs.z() > rhs.z())
            return false;
        else if (lhs.y() < rhs.y())
            return true;
        else if (lhs.y() > rhs.y())
            return false;
        else
            return (lhs.x() < rhs.x());
    }
};

#endif // UNIZCOMPAREFUCTOR_H
