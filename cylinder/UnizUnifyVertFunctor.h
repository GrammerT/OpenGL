#ifndef UNIZUNIFYVERTFUNCTOR_H
#define UNIZUNIFYVERTFUNCTOR_H

#include <QVector3D>
#include <map>
#include <array>
#include <QVector>
#include "UnizCompareFuctor.h"

struct UnizUnifyVertFunctor
{
    UnizUnifyVertFunctor()
        : _vertToIndexMap()
        , _vertices(NULL)
        , _indices(NULL)
    {}
    typedef unsigned int IndexType;
    typedef QVector<QVector3D> Vec3Array;
    typedef QVector<IndexType> IndexArray;

    std::map<QVector3D, IndexType, QVector3DCompare> _vertToIndexMap;
    Vec3Array *_vertices;
    IndexArray *_indices;

    void set(Vec3Array *vertices, IndexArray *indices)
    {
        _vertices = vertices;
        _indices = indices;
    }

    void reset()
    {
        _vertToIndexMap.clear();
        _vertices = NULL;
        _indices = NULL;
    }

    inline void operator()(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3)
    {
        std::array<QVector3D, 3> triangle = {v1, v2, v3};
        //! generate index and unique vertex
        for (int i=0; i<3; ++i)
        {
            auto iter = _vertToIndexMap.find(triangle[i]);
            if (iter != _vertToIndexMap.end())
            {
                 _indices->push_back(iter->second);
            }
            else
            {
                IndexType vertIndex = _vertices->size();
                _vertToIndexMap[triangle[i]] = vertIndex;
                _indices->push_back(vertIndex);
                _vertices->push_back(triangle[i]);
            }
        }
    }
};

#endif // UNIZUNIFYVERTFUNCTOR_H
