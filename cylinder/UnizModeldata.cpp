#include "UnizModeldata.h"
#include <math.h>
#include <QVector>
#include <QOpenGLShaderProgram>
#include "UnizBoundingBoxf.h"

struct CollectVertexesFunctor
{
    CollectVertexesFunctor() {}

    typedef QVector<QVector3D> Vec3Array;
    Vec3Array _vertexes;

    inline void operator()(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3)
    {
        _vertexes.push_back(v1);
        _vertexes.push_back(v2);
        _vertexes.push_back(v3);
    }
};

UnizModelData::UnizModelData()
    : mBoundingBox()
    , mArrayBufInitialized(false)
{
}

UnizModelData::~UnizModelData()
{
    if (mArrayBufInitialized)
    {
        mArrayBuffer->destroy();
        mIndexBuffer->destroy();
    }
}

void UnizModelData::setVertexArray(QSharedPointer<Vec3Array> array)
{
    m_pUniqueVertexes = array;
}

UnizModelData::Vec3Array *UnizModelData::getVertexArray()
{
    return m_pUniqueVertexes.data();
}

const UnizModelData::Vec3Array *UnizModelData::getVertexArray() const
{
    return m_pUniqueVertexes.data();
}

void UnizModelData::setNormalArray(QSharedPointer<Vec3Array> array)
{
    m_pNormals = array;
}

UnizModelData::Vec3Array *UnizModelData::getNormalArray()
{
    return m_pNormals.data();
}

const UnizModelData::Vec3Array *UnizModelData::getNormalArray() const
{
    return m_pNormals.data();
}

void UnizModelData::setIndiceArray(QSharedPointer<IndexArray> array)
{
    m_pIndices = array;
}

UnizModelData::IndexArray *UnizModelData::getIndexArray()
{
    return m_pIndices.data();
}

const UnizModelData::IndexArray *UnizModelData::getIndexArray() const
{
    return m_pIndices.data();
}

void UnizModelData::setHalfEdgeList(QSharedPointer<HalfEdgeList> halfedgeList)
{
    m_pHalfEdges = halfedgeList;
}

UnizModelData::HalfEdgeList *UnizModelData::getHalfEdgeList()
{
    return m_pHalfEdges.data();
}

const UnizModelData::HalfEdgeList *UnizModelData::getHalfEdgeList() const
{
    return m_pHalfEdges.data();
}

void UnizModelData::draw(QOpenGLShaderProgram &program)
{
    //! first draw call will initialize vbo
    if (!mArrayBufInitialized)
    {
        mArrayBufInitialized = true;
        initializeOpenGLFunctions();
        Vec3Array &vertexes = *m_pUniqueVertexes.data();

        mArrayBuffer = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer);
        qDebug()<<mArrayBuffer->create();
        qDebug()<<mArrayBuffer->bind();
        mArrayBuffer->allocate(&(vertexes[0]), sizeof(QVector3D)*vertexes.size());

        const IndexArray *pIndexs = m_pIndices.data();
        mIndexBuffer = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
        qDebug()<< mIndexBuffer->create();
        qDebug()<<mIndexBuffer->bind();
        mIndexBuffer->allocate(&(*pIndexs)[0], sizeof(unsigned int)*(pIndexs->size()));


        const Vec3Array *pNormals = m_pNormals.data();
        mNormalBuffer.create();
        mNormalBuffer.bind();
        mNormalBuffer.allocate(&(*pNormals)[0], sizeof(QVector3D)*(pNormals->size()));
    }
//    qDebug()<<mNormalBuffer.bind();
    int normalLocation = program.attributeLocation("VertexNormal");
    program.enableAttributeArray(normalLocation);
    program.setAttributeBuffer(normalLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

    qDebug()<<mArrayBuffer->bind();
    int vertexLocation = program.attributeLocation("VertexPosition");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

//    qDebug()<<mIndexBuffer->bind();


    glDrawElements(GL_TRIANGLES,m_pIndices.data()->size(),GL_UNSIGNED_INT,0);
}

void UnizModelData::correctVertexArray()
{
    Vec3Array *pVertices = m_pUniqueVertexes.data();

    if (!pVertices || pVertices->size()==0) return;

    Vec3Array &vertices = *pVertices;

    //! generate bounding box
    genBoundBox();

    QVector3D center = mBoundingBox.center();

    QVector3D offsetVec = QVector3D(center.x(), center.y(), center.z());

    for (int i=0; i<vertices.size(); ++i)
    {
        vertices[i] -= offsetVec;
    }

    QVector3D newMaxBound = QVector3D(mBoundingBox.xMax(), mBoundingBox.yMax(), mBoundingBox.zMax()) - offsetVec;
    QVector3D newMinBound = QVector3D(mBoundingBox.xMin(), mBoundingBox.yMin(), mBoundingBox.zMin()) - offsetVec;

    mBoundingBox.set(newMinBound, newMaxBound);
}

void UnizModelData::genBoundBox()
{
    Vec3Array *pVertices = m_pUniqueVertexes.data();

    if (!pVertices || pVertices->size()==0) return;

    Vec3Array &vertices = *pVertices;

    for (int i=0; i<vertices.size(); ++i)
    {
        mBoundingBox.expandBy(vertices[i]);
    }
}

void UnizModelData::accept(PrimitiveFunctor &functor) const
{
    Vec3Array *vertices = m_pUniqueVertexes.data();
    IndexArray *indices = m_pIndices.data();

    if (!vertices || vertices->size()==0 || !indices || indices->size()==0)
    {
        return;
    }

    functor.setVertexArray(vertices->size(), &(*vertices)[0]);
    functor.drawElements(GL_TRIANGLES, indices->size(), &(*indices)[0]);
}

void UnizModelData::accept(PrimitiveIndexFunctor &functor) const
{
    Vec3Array *vertices = m_pUniqueVertexes.data();
    IndexArray *indices = m_pIndices.data();

    if (!vertices || vertices->size()==0 || !indices || indices->size()==0)
    {
        return;
    }
    functor.setVertexArray(vertices->size(), &(*vertices)[0]);
    functor.drawElements(GL_TRIANGLES, indices->size(), &(*indices)[0]);
}

UnizBoundingBoxf UnizModelData::computeBoundingBox(const QMatrix4x4 &matrix, bool forceUpdate) const
{
    Q_UNUSED(forceUpdate);

    Vec3Array *pVertices = m_pUniqueVertexes.data();

    if (!pVertices || pVertices->size()==0) return UnizBoundingBoxf();

    Vec3Array &vertices = *pVertices;

    UnizBoundingBoxf bb;

    for (int i=0; i<vertices.size(); ++i)
    {
        bb.expandBy(matrix*vertices[i]);
    }

    return bb;
}
