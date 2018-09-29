#ifndef MODELDATA_H
#define MODELDATA_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QSharedPointer>
#include "UnizHalfEdge.h"
#include "UnizPrimitiveFunctor.h"
#include "UnizBoundingBoxf.h"

class QOpenGLShaderProgram;

/**
 * @brief The UnizModelData class
 * no longer have child data
 */
class UnizModelData : private QOpenGLFunctions
{
public:
    typedef QVector<QVector3D> Vec3Array;
    typedef QVector<unsigned int> IndexArray;
    typedef QVector<HalfEdge> HalfEdgeList;

    UnizModelData();
	~UnizModelData();

    void setVertexArray(QSharedPointer<Vec3Array> array);
    Vec3Array* getVertexArray();
    const Vec3Array* getVertexArray() const;

    void setNormalArray(QSharedPointer<Vec3Array> array);
    Vec3Array* getNormalArray();
    const Vec3Array* getNormalArray() const;

    void setIndiceArray(QSharedPointer<IndexArray> array);
    IndexArray* getIndexArray();
    const IndexArray* getIndexArray() const;

    void setHalfEdgeList(QSharedPointer<HalfEdgeList> halfedgeList);
    HalfEdgeList* getHalfEdgeList();
    const HalfEdgeList* getHalfEdgeList() const;

    void accept(PrimitiveFunctor &functor) const;
    void accept(PrimitiveIndexFunctor &functor) const;

    virtual UnizBoundingBoxf computeBoundingBox(const QMatrix4x4 &matrix, bool forceUpdate) const;

    //! draw in opengl context binded
    void draw(QOpenGLShaderProgram &program);

    //! correctVertexes can call when setVertexArray already set
    void correctVertexArray();

private:
    void genBoundBox();

    //! attribute arraylist
    QSharedPointer<Vec3Array> m_pUniqueVertexes;
    QSharedPointer<Vec3Array> m_pNormals;
    QSharedPointer<IndexArray> m_pIndices;

    //! topology data structure
    QSharedPointer<HalfEdgeList> m_pHalfEdges;

    //! bounding box
    UnizBoundingBoxf mBoundingBox;
	
    QSharedPointer<QOpenGLBuffer> mArrayBuffer;
    QSharedPointer<QOpenGLBuffer> mIndexBuffer;
    QSharedPointer<QOpenGLBuffer> mNormalBuffer;
    QOpenGLBuffer mColorBuffer;

    bool mArrayBufInitialized;
};
#endif
