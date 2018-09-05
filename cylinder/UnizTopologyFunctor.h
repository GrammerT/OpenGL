#ifndef UNIZTOPOLOGYFUNCTOR_H
#define UNIZTOPOLOGYFUNCTOR_H

#include "UnizHalfEdge.h"
#include <memory>
#include <array>
#include <QVector>
#include <map>

struct UnizTopologyFunctor
{
    UnizTopologyFunctor()
        : _hedges(NULL)
        , _hedgeBase(0)
        , _topologyStatus(true)
        , _mapEdges()
    {}

    typedef unsigned int IndexType;
    typedef std::pair<IndexType, IndexType> TriangleEdge;
    typedef QVector<HalfEdge> HalfEdgeList;

    HalfEdgeList *_hedges;
    unsigned int _hedgeBase;
    bool _topologyStatus;
    std::map<TriangleEdge, IndexType> _mapEdges;

    //! set valid hedge pointer to functor
    inline void setHedge(HalfEdgeList *hedges)
    {
        _hedges = hedges;
    }

    inline void reset()
    {
        _hedges = NULL;
        _hedgeBase = 0;
        _topologyStatus = true;
        _mapEdges.clear();
    }

    inline void checkTopologyStatus()
    {
        HalfEdgeList &halfEdges = *_hedges;

        //! check topology status
        for (const HalfEdge &halfEdge : halfEdges)
        {
            if (halfEdge.mPair == std::numeric_limits<IndexType>::max())
            {
                _topologyStatus = false;
                break;
            }
        }
    }

    inline void operator()(unsigned int p1, unsigned int p2, unsigned int p3)
    {
        std::array<unsigned int, 3> triangle = {p1, p2, p3};

        HalfEdgeList &halfEdges = *_hedges;
        for (int cIndex = 0; cIndex < 3; ++cIndex)
        {
            //! triangle vertex index
            int pIndex = (cIndex + 2) % 3;
            int nIndex = (cIndex + 1) % 3;

            //! calculate half edge index
            int nHedgeIndex = _hedgeBase + nIndex;
            int cHedgeIndex = _hedgeBase + cIndex;

            HalfEdge hEdge;
            hEdge.mNext = nHedgeIndex;
            hEdge.mEndVertex = triangle[cIndex];

            //! find pair halfedge
            TriangleEdge edge(triangle[pIndex], triangle[cIndex]);

            //! check topology status
            if(_mapEdges.find(edge) != _mapEdges.end())
                _topologyStatus = false;
            else
                _mapEdges[edge] = cHedgeIndex;

            TriangleEdge oppositeEdge(triangle[cIndex], triangle[pIndex]);

            if (_mapEdges.find(oppositeEdge) != _mapEdges.end())
            {
                hEdge.mPair = _mapEdges[oppositeEdge];
                halfEdges[hEdge.mPair].mPair = cHedgeIndex;
            }

            halfEdges.push_back(hEdge);
        }

        _hedgeBase += 3;
    }
};

#endif // UNIZTOPOLOGYFUNCTOR_H
