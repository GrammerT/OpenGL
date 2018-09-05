#ifndef FORMGRAPHICS_H
#define FORMGRAPHICS_H
#include <QVector3D>

class UnizModelData;

class FormGraphics
{
public:
    static void formCircle(UnizModelData *data, QVector3D center, float radius);

    static void formRoundTable(UnizModelData *data,QVector3D upCenter,float upRadius,QVector3D downCenter,float downRadius);

};

#endif // FORMGRAPHICS_H
