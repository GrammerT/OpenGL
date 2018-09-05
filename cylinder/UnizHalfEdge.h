#ifndef UNIZHALFEDGE_H
#define UNIZHALFEDGE_H

#include <limits>

struct HalfEdge
{
    unsigned int mEndVertex;		// vertex at the end of the half-edge
    unsigned int mPair;			// oppositely oriented adjacent half-edge
    unsigned int mNext;			// next half-edge around the face

    HalfEdge()
        : mEndVertex(std::numeric_limits<unsigned int>::max())
        , mPair(std::numeric_limits<unsigned int>::max())
        , mNext(std::numeric_limits<unsigned int>::max())
    {}
};

#endif // UNIZHALFEDGE_H
