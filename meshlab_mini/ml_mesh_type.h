#ifndef ML_MESH_TYPE_H
#define ML_MESH_TYPE_H
#include "vcg/complex/complex.h"
#include <QMatrix4x4>

class CVertex;
class CEdge;
class CFace;

struct CUsedType:public vcg::UsedTypes<vcg::Use<CVertex>::AsVertexType,
                                                                        vcg::Use<CFace>::AsFaceType,
                                                                        vcg::Use<CEdge>::AsEdgeType >
{};

class CVertex  : public vcg::Vertex<CUsedType, vcg::vertex::Coord3f, vcg::vertex::Normal3f, vcg::vertex::BitFlags>{};
class CFace    : public vcg::Face<CUsedType, vcg::face::FFAdj,  vcg::face::VertexRef, vcg::face::BitFlags > {};
class CEdge    : public vcg::Edge<CUsedType> {};


class CMeshO :public vcg::tri::TriMesh<std::vector<CVertex>,std::vector<CFace>,std::vector<CEdge>>
{
public :
    typedef vcg::Box3<float> Box3m;
    typedef vcg::Matrix44<float> Matrix44m;
    int sfn;//! selected faces
    int svn;//! selected vertices
    Matrix44m Tr;
    const Box3m &trBB()
    {
        static Box3m bb;
        bb.SetNull();
        bb.Add(Tr,bbox);
        return bb;
    }
};


#endif // ML_MESH_TYPE_H
