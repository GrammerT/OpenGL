#ifndef VBOTORUS_H
#define VBOTORUS_H
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

class VBOTorus : protected QOpenGLFunctions
{
public:
    VBOTorus(float outerRadius, float innerRadius, int nrings, int nsides);
    ~VBOTorus();
    void render();
    int getVertexArrayHandle();
protected:
    QOpenGLVertexArrayObject vao;
private:
    int faces, rings, sides;
    void generateVerts(float * verts, float * norms, float * tex,
                       unsigned int * el,
                       float outerRadius, float innerRadius);
};

#endif // VBOTORUS_H
