#ifndef EFFECTIVEPOINT_H
#define EFFECTIVEPOINT_H

#include <QPointF>
#include <QImage>

class EffectiveRect
{
public:
    EffectiveRect();

    QPointF center() const;
    void setCenter(const QPointF &center);

    QImage image() const;
    void setImage(const QImage &image);

private:
    QPointF _center;
    QImage _image;
};

#endif // EFFECTIVEPOINT_H
