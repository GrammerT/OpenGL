#include "UnizModeldata.h"
#include <math.h>
#include <QVector>
#include <QOpenGLShaderProgram>
#include <array>

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
    : mArrayBufInitialized(false)
    ,m_box(new Box)
    ,m_pEdge(new vec_HEDGE)
{
    m_pColors = QSharedPointer<Vec3Array>(new Vec3Array);
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
    m_pColors->push_back(QVector3D(1,0,0));
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


void UnizModelData::draw(QOpenGLShaderProgram &program)
{
    //! first draw call will initialize vbo
    if (!mArrayBufInitialized)
    {
        mArrayBufInitialized = true;
        initializeOpenGLFunctions();

        const Vec3Array &vertexes = *m_pUniqueVertexes.data();
        mArrayBuffer = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
        qDebug()<<mArrayBuffer->create();
        qDebug()<<mArrayBuffer->bind();
        mArrayBuffer->allocate(&(vertexes[0]), sizeof(QVector3D)*vertexes.size());

        const IndexArray *pIndexs = m_pIndices.data();
        mIndexBuffer = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
        qDebug()<< mIndexBuffer->create();
        qDebug()<<mIndexBuffer->bind();
        mIndexBuffer->allocate(&(*pIndexs)[0], sizeof(unsigned int)*(pIndexs->size()));
//        const Vec3Array *pNormals = m_pNormals.data();
//        mNormalBuffer = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
//        qDebug()<<mNormalBuffer->create();
//        qDebug()<<mNormalBuffer->bind();
//        mNormalBuffer->allocate(&(*pNormals)[0], sizeof(QVector3D)*(pNormals->size()));

    }

    qDebug()<<mIndexBuffer->bind();
//    qDebug()<<mNormalBuffer->bind();
//    int normalLocation = program.attributeLocation("VertexNormal");
//    program.enableAttributeArray(normalLocation);
//    program.setAttributeBuffer(normalLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

    qDebug()<<mArrayBuffer->bind();
    int vertexLocation = program.attributeLocation("VertexPosition");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

    glDrawElements(GL_TRIANGLES,m_pIndices.data()->size(),GL_UNSIGNED_INT,0);

}

void UnizModelData::drawByDiffColors(QOpenGLShaderProgram &program)
{

}

QSharedPointer<Box> UnizModelData::boundingBox(QMatrix4x4 matrix)
{
    for(int i=0;i<m_pUniqueVertexes->size();++i)
    {
        m_box->calculateBox(matrix*(m_pUniqueVertexes->data())[i]);
    }
    m_box->updataData();
    return m_box;
}

UnizModelData::Vec3Array *UnizModelData::getPDiffColors() const
{
    return m_pDiffColors.data();
}

void UnizModelData::setPDiffColors(const QSharedPointer<Vec3Array> &pDiffColors)
{
    m_pDiffColors = pDiffColors;
}

QSharedPointer<vec_HEDGE> UnizModelData::getPEdge() const
{
    return m_pEdge;
}

void UnizModelData::setPEdge(const QSharedPointer<vec_HEDGE> &pEdge)
{
    m_pEdge = pEdge;
}

typedef std::pair<IndexType, IndexType> TriangleEdge;

void UnizModelData::formHedge(unsigned int p1, unsigned int p2, unsigned int p3)
{
    static int _hedgeBase = 0;
    static std::map<TriangleEdge, IndexType> _mapEdges;
    std::array<unsigned int ,3> triangle ={p1,p2,p3};
    vec_HEDGE &halfEdge = *(m_pEdge.data());
    for(int cIndex = 0;cIndex<3;++cIndex)
    {
        int pIndex = (cIndex+2)%3;
        int nIndex = (cIndex+1)%3;

        int nHedgeIndex = _hedgeBase+nIndex;
        int cHedgeIndex = _hedgeBase+cIndex;

        HEDGE hEdge;
        hEdge.mNext = nHedgeIndex;
        hEdge.mEndVertex = triangle[cIndex];

        TriangleEdge edge(triangle[pIndex],triangle[cIndex]);

        if(_mapEdges.find(edge)!=_mapEdges.end())
        {

        }
        else
        {
            _mapEdges[edge] = cHedgeIndex;
        }
        TriangleEdge oppositeEdge(triangle[cIndex], triangle[pIndex]);
        if(_mapEdges.find(oppositeEdge)!=_mapEdges.end())
        {
            hEdge.mPair=_mapEdges[oppositeEdge];
            halfEdge[hEdge.mPair].mPair = cHedgeIndex;
        }
        halfEdge.push_back(hEdge);
    }
    _hedgeBase += 3;
}

UnizModelData::Vec3Array* UnizModelData::getPColors() const
{
    return m_pColors.data();
}

void UnizModelData::setPColors(const QSharedPointer<Vec3Array> &pColors)
{
    m_pColors = pColors;
}



void Box::reset()
{
    max.setX(-FLT_MAX);
    max.setY(-FLT_MAX);
    max.setZ(-FLT_MAX);

    min.setX(FLT_MAX);
    min.setY(FLT_MAX);
    min.setZ(FLT_MAX);
}

void Box::calculateBox(QVector3D vertex)
{
    if(max.x()<vertex.x())
        max.setX(vertex.x());
    if(min.x()>vertex.x())
        min.setX(vertex.x());

    if(max.y()<vertex.y())
        max.setY(vertex.y());
    if(min.y()>vertex.y())
        min.setY(vertex.y());

    if(max.z()<vertex.z())
        max.setZ(vertex.z());
    if(min.z()>vertex.z())
        min.setZ(vertex.z());
}

void Box::draw(QOpenGLShaderProgram &program)
{
    //! first draw call will initialize vbo

    if (!mArrayBufInitialized)
    {
        mArrayBufInitialized = true;
        initializeOpenGLFunctions();

        mArrayBuffer = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
        qDebug()<<mArrayBuffer->create();
        qDebug()<<mArrayBuffer->bind();
        mArrayBuffer->allocate(&(_data[0]), sizeof(QVector3D)*_data.size());

        mIndexBuffer = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
        qDebug()<< mIndexBuffer->create();
        qDebug()<<mIndexBuffer->bind();
        mIndexBuffer->allocate(&(_index[0]), sizeof(unsigned int)*(_index.size()));
    }
    qDebug()<<mIndexBuffer->bind();
    qDebug()<<mArrayBuffer->bind();
    glLineWidth(2);
    int vertexLocation = program.attributeLocation("VertexPosition");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));
    glDrawElements(GL_QUADS,_index.size(),GL_UNSIGNED_INT,0);
}

void Box::updataData()
{
    qDebug()<<"----1-----"<<_data;
    _data.clear();

    _data.push_back(QVector3D(max.x(),max.y(),max.z()));
    _data.push_back(QVector3D(max.x(),min.y(),max.z()));
    _data.push_back(QVector3D(max.x(),min.y(),min.z()));
    _data.push_back(QVector3D(max.x(),max.y(),min.z()));

    _data.push_back(QVector3D(min.x(),max.y(),max.z()));
    _data.push_back(QVector3D(min.x(),min.y(),max.z()));
    _data.push_back(QVector3D(min.x(),min.y(),min.z()));
    _data.push_back(QVector3D(min.x(),max.y(),min.z()));
    qDebug()<<"----2-----"<<_data;
    mArrayBufInitialized = false;
}
