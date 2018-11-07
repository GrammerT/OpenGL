#ifndef SUPPORTTOOL_H
#define SUPPORTTOOL_H
#include <QRectF>
#include "effectiverect.h"



inline bool Contain(const QRectF &rect,const EffectiveRect &erect)
{
    return rect.contains(erect.center());
}


#endif // SUPPORTTOOL_H
