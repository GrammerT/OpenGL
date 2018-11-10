#ifndef MODELDATA_H
#define MODELDATA_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QSharedPointer>
#include <QVector3D>
#include <QVector>

class QOpenGLShaderProgram;

/**
 * @brief The UnizModelData class
 * no longer have child data
 */
typedef unsigned int IndexType;

typedef struct HalfEdge
{
    IndexType mEndVertex;		// vertex at the end of the half-edge
    IndexType mPair;			// oppositely oriented adjacent half-edge
    IndexType mNext;			// next half-edge around the face
    bool bStatus;				// �����������Ƿ����õ�
    HalfEdge()
        : mEndVertex(std::numeric_limits<IndexType>::max())
        , mPair(std::numeric_limits<IndexType>::max())
        , mNext(std::numeric_limits<IndexType>::max())
        , bStatus(false)
    {

    }
}HEDGE;

typedef QVector<HEDGE> vec_HEDGE;

class Box : private QOpenGLFunctions
{
    typedef QVector<QVector3D> Vec3Array;
    typedef QVector<unsigned int> IndexArray;
public:
    Box()
        :mArrayBufInitialized(false)
    {
        max.setX(-FLT_MAX);
        max.setY(-FLT_MAX);
        max.setZ(-FLT_MAX);

        min.setX(FLT_MAX);
        min.setY(FLT_MAX);
        min.setZ(FLT_MAX);

        _data.push_back(QVector3D(max.x(),max.y(),max.z()));
        _data.push_back(QVector3D(max.x(),min.y(),max.z()));
        _data.push_back(QVector3D(max.x(),min.y(),min.z()));
        _data.push_back(QVector3D(max.x(),max.y(),min.z()));

        _data.push_back(QVector3D(min.x(),max.y(),max.z()));
        _data.push_back(QVector3D(min.x(),min.y(),max.z()));
        _data.push_back(QVector3D(min.x(),min.y(),min.z()));
        _data.push_back(QVector3D(min.x(),max.y(),min.z()));

        _index.push_back(0);
        _index.push_back(1);
        _index.push_back(2);
        _index.push_back(3);

        _index.push_back(2);
        _index.push_back(6);
        _index.push_back(7);
        _index.push_back(3);

        _index.push_back(4);
        _index.push_back(7);
        _index.push_back(6);
        _index.push_back(5);

        _index.push_back(1);
        _index.push_back(0);
        _index.push_back(4);
        _index.push_back(5);

        _index.push_back(0);
        _index.push_back(3);
        _index.push_back(7);
        _index.push_back(4);

        _index.push_back(1);
        _index.push_back(5);
        _index.push_back(6);
        _index.push_back(2);
    }
    void reset();

    void calculateBox(QVector3D vertex);

    float left()
    {
        return min.x();
    }

    float right()
    {
        return max.x();
    }

    float up()
    {
        return max.y();
    }

    float down()
    {
        return min.y();
    }

    QVector3D center()
    {
        return  (max+min)*0.5;
    }

    void draw(QOpenGLShaderProgram &program);
    void updataData();
private:
public:
    bool mArrayBufInitialized;
    QVector3D max;
    QVector3D min;
    Vec3Array _data;
    IndexArray _index;
    QSharedPointer<QOpenGLBuffer> mArrayBuffer;
    QSharedPointer<QOpenGLBuffer> mIndexBuffer;

};

class UnizModelData : private QOpenGLFunctions
{
public:
    typedef QVector<QVector3D> Vec3Array;
    typedef QVector<QVector4D> Vec4Array;
    typedef QVector<unsigned int> IndexArray;

    UnizModelData();
	~UnizModelData();

    void setVertexArray(QSharedPointer<Vec3Array> array);
    Vec3Array* getVertexArray();
    const Vec3Array* getVertexArray() const;

    void setNormalArray(QSharedPointer<Vec3Array> array);
    Vec3Array* getNormalArray();
    const Vec3Array* getNormalArray() const;

    Vec3Array *getPColors() const;
    void setPColors(const QSharedPointer<Vec3Array> &pColors);

    void setIndiceArray(QSharedPointer<IndexArray> array);
    IndexArray* getIndexArray();
    const IndexArray* getIndexArray() const;

    //! draw in opengl context binded
    void draw(QOpenGLShaderProgram &program);

    void drawByDiffColors(QOpenGLShaderProgram &program);

    //! correctVertexes can call when setVertexArray already set
    void correctVertexArray();

    QSharedPointer<Box> boundingBox(QMatrix4x4 matrix);

    Vec4Array* getPDiffColors() const;
    void setPDiffColors(const QSharedPointer<Vec4Array> &pDiffColors);

    QSharedPointer<vec_HEDGE> getPEdge() const;
    void setPEdge(const QSharedPointer<vec_HEDGE> &pEdge);

    void formHedge(unsigned int p1, unsigned int p2, unsigned int p3);
    void formColors(unsigned int p1, unsigned int p2, unsigned int p3);
private:

    //! attribute arraylist
    QSharedPointer<Vec3Array> m_pUniqueVertexes;
    QSharedPointer<Vec3Array> m_pNormals;
    QSharedPointer<Vec3Array> m_pColors;
    QSharedPointer<Vec4Array> m_pDiffColors;
    QSharedPointer<IndexArray> m_pIndices;
    QSharedPointer<Box> m_box;
	
    QSharedPointer<vec_HEDGE> m_pEdge;

    QSharedPointer<QOpenGLBuffer> mArrayBuffer;
    QSharedPointer<QOpenGLBuffer> mIndexBuffer;
    QSharedPointer<QOpenGLBuffer> mNormalBuffer;
    QOpenGLBuffer mColorBuffer;

    bool mArrayBufInitialized;
};
#endif
