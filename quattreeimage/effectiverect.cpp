#include "effectiverect.h"

EffectiveRect::EffectiveRect()
{

}

QPointF EffectiveRect::center() const
{
    return _center;
}

void EffectiveRect::setCenter(const QPointF &center)
{
    _center = center;
}

QImage EffectiveRect::image() const
{
    return _image;
}

void EffectiveRect::setImage(const QImage &image)
{
    _image = image;
}
