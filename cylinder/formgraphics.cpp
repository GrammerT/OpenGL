#include "formgraphics.h"
#include <QtMath>
#include <array>
#include <QVector3D>
#include <QVector>
#include <QSharedPointer>
#include "UnizModeldata.h"
#include "UnizGenNormalFunctor.h"
#include "UnizTopologyFunctor.h"
#include "UnizUnifyVertFunctor.h"
#include <QDebug>

void FormGraphics::formCircle(UnizModelData *data, QVector3D center, float radius)
{
    typedef QVector<QVector3D> Vec3Array;
    typedef QVector<unsigned int> IndexArray;
    QSharedPointer<Vec3Array> spVertices(new Vec3Array);
    QSharedPointer<IndexArray> spIndices(new IndexArray);
    Vec3Array *pVertices = spVertices.data();
    IndexArray *pIndices = spIndices.data();
    int M = 20; //! 经度
    int N = 20; //! 纬度
    float step_z = M_PI/M;
    float step_xy = 2*M_PI/N;
    float angle_z = 0.0;
    float angle_xy = 0.0;
    int i=0, j=0;

    float x,y,z;
    x = 0.0;
    y = 0.0;
    z = radius * cos(0);
    QVector3D UP = QVector3D(x,y,z);

    x = 0.0;
    y = 0.0;
    z = radius * cos(M_PI);
    QVector3D DOWN = QVector3D(x,y,z);

    typedef QVector<QVector<QVector3D>>  RingPoints;
    RingPoints points;
    //! rotate by Y
    //! angle_z: 与z轴正向夹角
    //! angle_xy:与x轴正向夹角
    for(i=1; i<M; i++)
    {
        QVector<QVector3D> oneRingPoints;
        QVector3D point;
        angle_z = i * step_z;
        for(j=0; j<N; j++)
        {
            angle_xy = j * step_xy;
            point.setX(radius * sin(angle_z) * cos(angle_xy));
            point.setY(radius * sin(angle_z) * sin(angle_xy));
            point.setZ(radius *cos(angle_z));
            oneRingPoints.push_back(point);
        }
        points.push_back(oneRingPoints);
    }
//    UP
    QVector<QVector3D> tmpPoint = points[0];
    for(int i=0;i<tmpPoint.size();++i)
    {
        unsigned int ind= pVertices->size();
        QVector3D p1,p2,p3;
        p1 = UP;
        p2 = tmpPoint[i];
        if(i==tmpPoint.size()-1)
        {
            p3 = tmpPoint[0];
        }
        else
        {
            p3 = tmpPoint[i+1];
        }
        pVertices->push_back(p1);
        pIndices->push_back(ind);
        pVertices->push_back(p2);
        pIndices->push_back(ind+1);
        pVertices->push_back(p3);
        pIndices->push_back(ind+2);
    }
    for(int i=0;i<points.size()-1;++i)
    {
        QVector<QVector3D> tmpLines1 = points[i];
        QVector<QVector3D> tmpLines2 = points[i+1];
        for(int j=0;j<tmpLines1.size();++j)
        {
            QVector3D up1 = tmpLines1[j];
            QVector3D up2;
            QVector3D down1 = tmpLines2[j];
            QVector3D down2;
            if(j==tmpLines1.size()-1)
            {
                up2 = tmpLines1[0];
                down2 = tmpLines2[0];
            }
            else
            {
                up2 = tmpLines1[j+1];
                down2 = tmpLines2[j+1];
            }
             //! 1
            unsigned int ind= pVertices->size();
            pVertices->push_back(down1);
            pIndices->push_back(ind);
            pVertices->push_back(down2);
            pIndices->push_back(ind+1);
            pVertices->push_back(up1);
            pIndices->push_back(ind+2);
            //! 2
            ind= pVertices->size();
            pVertices->push_back(down2);
            pIndices->push_back(ind);
            pVertices->push_back(up2);
            pIndices->push_back(ind+1);
            pVertices->push_back(up1);
            pIndices->push_back(ind+2);
        }
    }
    //! DOWN
    QVector<QVector3D> tmpPoint1 = points[points.size()-1];
    for(int i=0;i<tmpPoint1.size();++i)
    {
        unsigned int ind= pVertices->size();
        QVector3D p1,p2,p3;
        p1 = DOWN;
        p2 = tmpPoint1[i];
        if(i==tmpPoint1.size()-1)
        {
            p3 = tmpPoint1[0];
        }
        else
        {
            p3 = tmpPoint1[i+1];
        }
        pVertices->push_back(p1);
        pIndices->push_back(ind);
        pVertices->push_back(p3);
        pIndices->push_back(ind+1);
        pVertices->push_back(p2);
        pIndices->push_back(ind+2);
    }

    data->setIndiceArray(spIndices);
    data->setVertexArray(spVertices);

    QSharedPointer<Vec3Array> spVertices1(new Vec3Array);
    QSharedPointer<IndexArray> spIndices1(new IndexArray);
    TriangleFunctor<UnizUnifyVertFunctor> uvf;
    uvf.set(spVertices1.data(),spIndices1.data());
    data->accept(uvf);

    data->setIndiceArray(spIndices1);
    data->setVertexArray(spVertices1);
    data->correctVertexArray();

    QSharedPointer<UnizModelData::Vec3Array> spNormals(new UnizModelData::Vec3Array);
    TriangleFunctor<UnizGenNormalFunctor> gnf;
    gnf.set(spNormals.data());
    data->accept(gnf);
    data->setNormalArray(spNormals);

    QSharedPointer<UnizModelData::HalfEdgeList> hedgeList(new UnizModelData::HalfEdgeList);
    TriangleIndexFunctor<UnizTopologyFunctor> utf;
    utf.setHedge(hedgeList.data());
    data->accept(utf);
    data->setHalfEdgeList(hedgeList);
}

void FormGraphics::formRoundTable(UnizModelData *data, QVector3D upCenter, float upRadius,
                                                                                            QVector3D downCenter, float downRadius)
{
    typedef QVector<QVector3D> Vec3Array;
    typedef QVector<unsigned int> IndexArray;

    QSharedPointer<Vec3Array> spVertices(new Vec3Array);
    QSharedPointer<IndexArray> spIndices(new IndexArray);
    Vec3Array *pVertices = spVertices.data();
    IndexArray *pIndices = spIndices.data();

    float roundTableLength = upCenter.distanceToPoint(downCenter);

    int M = 1; //! 经度
    int N = 10; //! 纬度

    float step_xy = 2*M_PI/N; //! N边形
    float angle_xy = 0.0;
    float x,y,z;
    x = 0.0;
    y = 0.0;
    z = roundTableLength*0.5;
    QVector3D UP = QVector3D(x,y,z);

    x = 0;
    y = 0;
    z = roundTableLength*0.5;
    QVector3D DOWN = QVector3D(x,y,-z);

    typedef QVector<QVector<QVector3D>>  RingPoints;
    //! rotate by Y
    //! angle_z: 与z轴正向夹角
    //! angle_xy:与x轴正向夹角
    //! up round
    RingPoints uppoints;
    QVector<QVector3D> upRingPoints;
    {
        QVector3D upPoint;
        for(int j=0; j<N; j++)
        {
            angle_xy = j * step_xy;
            upPoint.setX(upRadius * cos(angle_xy));
            upPoint.setY(upRadius * sin(angle_xy));
            upPoint.setZ(roundTableLength*0.5);
            upRingPoints.push_back(upPoint);
        }
        uppoints.push_back(upRingPoints);
    }
    //! down round
    RingPoints downpoints;
    QVector<QVector3D> downRingPoints;
    {
        angle_xy = 0.0;
        QVector3D downpoint;
        for(int j=0; j<N; j++)
        {
            angle_xy = j * step_xy;
            downpoint.setX(downRadius * cos(angle_xy));
            downpoint.setY(downRadius * sin(angle_xy));
            downpoint.setZ(-roundTableLength*0.5);
            downRingPoints.push_back(downpoint);
        }
        downpoints.push_back(downRingPoints);
    }

    for(int i=0;i<upRingPoints.size();++i)
    {
        QVector3D p1,p2,p3;
        p1 = UP;
        p2 = upRingPoints[i];
        if(i==upRingPoints.size()-1)
        {
            p3 = upRingPoints[0];
        }
        else
        {
            p3 = upRingPoints[i+1];
        }
        unsigned int ind= pVertices->size();
        pVertices->push_back(p1);
        pIndices->push_back(ind);
        pVertices->push_back(p2);
        pIndices->push_back(ind+1);
        pVertices->push_back(p3);
        pIndices->push_back(ind+2);
    }
    for(int i=0;i<downRingPoints.size();++i)
    {
        QVector3D p1,p2,p3;
        p1 = DOWN;
        p2 = downRingPoints[i];
        if(i==downRingPoints.size()-1)
        {
            p3 = downRingPoints[0];
        }
        else
        {
            p3 = downRingPoints[i+1];
        }
        unsigned int ind= pVertices->size();
        pVertices->push_back(p1);
        pIndices->push_back(ind);
        pVertices->push_back(p3);
        pIndices->push_back(ind+1);
        pVertices->push_back(p2);
        pIndices->push_back(ind+2);
    }
    for(int j=0;j<upRingPoints.size();++j)
    {
        QVector3D up1 = upRingPoints[j];
        QVector3D up2;
        QVector3D down1 = downRingPoints[j];
        QVector3D down2;
        if(j==upRingPoints.size()-1)
        {
            up2 = upRingPoints[0];
            down2 = downRingPoints[0];
        }
        else
        {
            up2 = upRingPoints[j+1];
            down2 = downRingPoints[j+1];
        }
        //! 1
        unsigned int ind= pVertices->size();
        pVertices->push_back(down1);
        pIndices->push_back(ind);
        pVertices->push_back(down2);
        pIndices->push_back(ind+1);
        pVertices->push_back(up1);
        pIndices->push_back(ind+2);
        //! 2
        ind= pVertices->size();
        pVertices->push_back(down2);
        pIndices->push_back(ind);
        pVertices->push_back(up2);
        pIndices->push_back(ind+1);
        pVertices->push_back(up1);
        pIndices->push_back(ind+2);
    }

    data->setIndiceArray(spIndices);
    data->setVertexArray(spVertices);

    QSharedPointer<Vec3Array> spVertices1(new Vec3Array);
    QSharedPointer<IndexArray> spIndices1(new IndexArray);
    TriangleFunctor<UnizUnifyVertFunctor> uvf;
    uvf.set(spVertices1.data(),spIndices1.data());
    data->accept(uvf);

    data->setIndiceArray(spIndices1);
    data->setVertexArray(spVertices1);
    data->correctVertexArray();

    QSharedPointer<UnizModelData::Vec3Array> spNormals(new UnizModelData::Vec3Array);
    TriangleFunctor<UnizGenNormalFunctor> gnf;
    gnf.set(spNormals.data());
    data->accept(gnf);
    data->setNormalArray(spNormals);

//    QSharedPointer<UnizModelData::HalfEdgeList> hedgeList(new UnizModelData::HalfEdgeList);
//    TriangleIndexFunctor<UnizTopologyFunctor> utf;
//    utf.setHedge(hedgeList.data());
//    data->accept(utf);
//    data->setHalfEdgeList(hedgeList);
}

void FormGraphics::formSupportTouch(UnizModelData *data)
{

}



void FormGraphics::formSupportHead(UnizModelData *data)
{

}

void FormGraphics::formSupportBody(UnizModelData *data)
{

}

void FormGraphics::formSupportFoot(UnizModelData *data)
{

}
