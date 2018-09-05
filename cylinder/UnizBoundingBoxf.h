#ifndef UNIZBOUNDINGBOXF_H
#define UNIZBOUNDINGBOXF_H

#include <QVector3D>
#include <float.h>
#include <math.h>

class UnizBoundingBoxf
{
public:
    UnizBoundingBoxf()
        : mMin(FLT_MAX, FLT_MAX, FLT_MAX)
        , mMax(-FLT_MAX, -FLT_MAX, -FLT_MAX)
    {}

    UnizBoundingBoxf(const QVector3D &min, const QVector3D &max)
        : mMin(min)
        , mMax(max)
    {}

    UnizBoundingBoxf(const UnizBoundingBoxf &bb)
        : mMin(bb.mMin)
        , mMax(bb.mMax)
    {}

    //! reset to init status
    void reset()
    {
        mMin.setX(FLT_MAX);
        mMin.setY(FLT_MAX);
        mMin.setZ(FLT_MAX);

        mMax.setX(-FLT_MAX);
        mMax.setY(-FLT_MAX);
        mMax.setZ(-FLT_MAX);
    }

    bool valid() const
    {
        return mMax.x()>=mMin.x() && mMax.y()>=mMin.y() && mMax.z()>=mMin.z();
    }

    //! setter
    void set(const QVector3D &min, const QVector3D &max)
    {
        mMin = min;
        mMax = max;
    }

    //! getter
    float xMin() const { return mMin.x(); }
    float yMin() const { return mMin.y(); }
    float zMin() const { return mMin.z(); }

    float xMax() const { return mMax.x(); }
    float yMax() const { return mMax.y(); }
    float zMax() const { return mMax.z(); }

    QVector3D center() const
    {
        return (mMax+mMin)*0.5;
    }

    float radius() const
    {
        return sqrtf(radius2());
    }

    float radius2() const
    {
        return 0.25*((mMax-mMin).lengthSquared());
    }

    float length() const
    {
        return xMax() - xMin();
    }

    float width() const
    {
        return yMax() - yMin();
    }

    float height() const
    {
        return zMax() - zMin();
    }

    //! modify boundingBox
    void expandBy(float x, float y, float z)
    {
        if (x < mMin.x()) mMin.setX(x);
        if (x > mMax.x()) mMax.setX(x);

        if (y < mMin.y()) mMin.setY(y);
        if (y > mMax.y()) mMax.setY(y);

        if (z < mMin.z()) mMin.setZ(z);
        if (z > mMax.z()) mMax.setZ(z);
    }

    void expandBy(const QVector3D &vertex)
    {
        expandBy(vertex.x(), vertex.y(), vertex.z());
    }

    void expandBy(const UnizBoundingBoxf &bb)
    {
        if (!bb.valid()) return;

        expandBy(bb.mMax);
        expandBy(bb.mMin);
    }

    //! return true if this bounding box intersects the specified boundingbox
    bool intersects(const UnizBoundingBoxf &bb) const
    {
        return (fmax(xMin(), bb.xMin()) <= fmin(xMax(), bb.xMax())) &&
                (fmax(yMin(), bb.yMin()) <= fmin(yMax(), bb.yMax())) &&
                (fmax(zMin(), bb.zMin()) <= fmin(zMax(), bb.zMax()));
    }

    //! return true if this bounding box contains this specified coordinate.
    bool contains(const QVector3D &vertex) const
    {
        return valid() &&
                (vertex.x()>=mMin.x() && vertex.x()<=mMax.x()) &&
                (vertex.y()>=mMin.y() && vertex.y()<=mMax.y()) &&
                (vertex.z()>=mMin.z() && vertex.z()<=mMax.z());
    }

private:

    //! max and min point
    QVector3D mMin;
    QVector3D mMax;
};

#endif // UNIZBOUNDINGBOXF_H
