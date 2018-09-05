#ifndef UNIZPRIMITIVEFUNCTOR_H
#define UNIZPRIMITIVEFUNCTOR_H

#include <gl/GL.h>
#include <gl/GLU.h>
#include <QVector3D>

class PrimitiveFunctor
{
public:
    virtual ~PrimitiveFunctor() {}

    virtual void setVertexArray(unsigned int count, const QVector3D *vertices) = 0;

    virtual void drawArrays(GLenum mode, GLint first, GLsizei count) = 0;
    virtual void drawElements(GLenum mode, GLsizei count, const GLuint *indices) = 0;
};

class PrimitiveIndexFunctor
{
public:
    virtual ~PrimitiveIndexFunctor() {}
    virtual void setVertexArray(unsigned int count, const QVector3D *vertices) = 0;
    virtual void drawArrays(GLenum mode, GLint first, GLsizei count) = 0;
    virtual void drawElements(GLenum mode, GLsizei count, const GLuint *indices) = 0;
};

template<typename T>
class TriangleIndexFunctor : public PrimitiveIndexFunctor, public T
{
public:
    virtual void setVertexArray(unsigned int count, const QVector3D *vertices){}

    virtual void drawArrays(GLenum mode, GLint first, GLsizei count)
    {
        switch (mode) {
        case (GL_TRIANGLES):
        {
            unsigned int pos=first;
            for(GLsizei i=2; i<count; i+=3, pos+=3)
            {
                this->operator()(pos, pos+1, pos+2);
            }
            break;
        }
        case (GL_TRIANGLE_STRIP):
        {
            unsigned int pos=first;
            for(GLsizei i=2; i<count; ++i,++pos)
            {
                if (i%2) this->operator()(pos,pos+2,pos+1);
                else this->operator()(pos,pos+1,pos+2);
            }
            break;
        }
        case (GL_QUADS):
        {
            unsigned int pos=first;
            for(GLsizei i=3;i<count;i+=4,pos+=4)
            {
                this->operator()(pos,pos+1,pos+2);
                this->operator()(pos,pos+2,pos+3);
            }
            break;
        }
        case(GL_QUAD_STRIP):
        {
            unsigned int pos=first;
            for(GLsizei i=3;i<count;i+=2,pos+=2)
            {
                this->operator()(pos,pos+1,pos+2);
                this->operator()(pos+1,pos+3,pos+2);
            }
            break;
        }
        case(GL_POLYGON): //! treat polygons as GL_TRIANGLE_FAN
        case(GL_TRIANGLE_FAN):
        {
            unsigned int pos=first+1;
            for(GLsizei i=2;i<count;++i,++pos)
            {
                this->operator()(first,pos,pos+1);
            }
            break;
        }
        case(GL_POINTS):
        case(GL_LINES):
        case(GL_LINE_STRIP):
        case(GL_LINE_LOOP):
        default:
            //! can not be converted into to triangles
            break;
        }
    }

    virtual void drawElements(GLenum mode, GLsizei count, const GLuint *indices)
    {
        if (indices==0 || count==0) return;

        switch (mode) {
        case (GL_TRIANGLES):
        {
            const GLuint *iLast = &indices[count];
            for (const GLuint *iptr=indices; iptr<iLast; iptr+=3)
            {
                this->operator()(*iptr, *(iptr+1), *(iptr+2));
            }
            break;
        }
        case (GL_TRIANGLE_STRIP):
        {
            const GLuint *iptr = indices;
            for(GLsizei i=2; i<count; ++i,++iptr)
            {
                if ((i%2)) this->operator()(*(iptr), *(iptr+2), *(iptr+1));
                else this->operator()(*(iptr), *(iptr+1), *(iptr+2));
            }
            break;
        }
        case (GL_QUADS):
        {
            const GLuint *iptr = indices;
            for (GLsizei i=3; i<count; i+=4, iptr+=4)
            {
                this->operator()(*(iptr),*(iptr+1),*(iptr+2));
                this->operator()(*(iptr),*(iptr+2),*(iptr+3));
            }
            break;
        }
        case (GL_QUAD_STRIP):
        {
            const GLuint *iptr = indices;
            for(GLsizei i=3;i<count;i+=2,iptr+=2)
            {
                this->operator()(*(iptr),*(iptr+1),*(iptr+2));
                this->operator()(*(iptr+1),*(iptr+3),*(iptr+2));
            }
            break;
        }
        case(GL_POLYGON): //! treat polygons as GL_TRIANGLE_FAN
        case(GL_TRIANGLE_FAN):
        {
            const GLuint *iptr = indices;
            GLuint first = *iptr;
            ++iptr;
            for(GLsizei i=2;i<count;++i,++iptr)
            {
                this->operator()(first,*(iptr),*(iptr+1));
            }
            break;
        }
        case(GL_POINTS):
        case(GL_LINES):
        case(GL_LINE_STRIP):
        case(GL_LINE_LOOP):
        default:
            //! can not converted into to triangles
            break;
        }
    }
};

template<typename T>
class TriangleFunctor : public PrimitiveFunctor, public T
{
public:
    TriangleFunctor()
    {
        mVertexArraySize = 0;
        mVertexArrayPtr = NULL;
    }

    virtual ~TriangleFunctor() {}

    virtual void setVertexArray(unsigned int count, const QVector3D *vertices)
    {
        mVertexArraySize = count;
        mVertexArrayPtr = vertices;
    }

    virtual void drawArrays(GLenum mode, GLint first, GLsizei count)
    {
        if (mVertexArrayPtr==NULL || mVertexArraySize==0) return;

        switch (mode) {
        case (GL_TRIANGLES):
        {
            const QVector3D *vLast = &mVertexArrayPtr[first+count];
            for (const QVector3D *vptr=&mVertexArrayPtr[first]; vptr<vLast; vptr+=3)
            {
                this->operator()(*(vptr), *(vptr+1), *(vptr+2));
            }
            break;
        }
        case (GL_TRIANGLE_STRIP):
        {
            const QVector3D *vptr = &mVertexArrayPtr[first];
            for(GLsizei i=2; i<count; ++i,++vptr)
            {
                if ((i%2)) this->operator()(*(vptr), *(vptr+2), *(vptr+1));
                else this->operator()(*(vptr), *(vptr+1), *(vptr+2));
            }
            break;
        }
        case (GL_QUADS):
        {
            const QVector3D *vptr = &mVertexArrayPtr[first];
            for(GLsizei i=3; i<count; i+=4,vptr+=4)
            {
                this->operator()(*(vptr), *(vptr+1), *(vptr+2));
                this->operator()(*(vptr), *(vptr+2), *(vptr+3));
            }
            break;
        }
        case (GL_QUAD_STRIP):
        {
            const QVector3D *vptr = &mVertexArrayPtr[first];
            for(GLsizei i=3; i<count; i+=2,vptr+=2)
            {
                this->operator()(*(vptr), *(vptr+1), *(vptr+2));
                this->operator()(*(vptr+1), *(vptr+3), *(vptr+2));
            }
            break;
        }
        case (GL_POLYGON): //! treat polygons as GL_TRIANGLE_FAN
        case (GL_TRIANGLE_FAN):
        {
            const QVector3D *vfirst = &mVertexArrayPtr[first];
            const QVector3D *vptr = vfirst+1;
            for (GLsizei i=2; i<count; ++i,++vptr)
            {
                this->operator()(*(vfirst), *(vptr), *(vptr+1));
            }
            break;
        }
        case (GL_POINTS):
        case (GL_LINES):
        case (GL_LINE_STRIP):
        case (GL_LINE_LOOP):
        default:
            //! can not be converted into triangles
            break;
        }
    }

    virtual void drawElements(GLenum mode, GLsizei count, const GLuint *indices)
    {
        if (indices==0 || count==0) return;
        if (mVertexArrayPtr==NULL || mVertexArraySize==0) return;

        switch (mode) {
        case (GL_TRIANGLES):
        {
            const GLuint *iLast = &indices[count];
            for (const GLuint *iptr=indices; iptr<iLast; iptr+=3)
            {
                this->operator()(mVertexArrayPtr[*iptr], mVertexArrayPtr[*(iptr+1)], mVertexArrayPtr[*(iptr+2)]);
            }
            break;
        }
        case (GL_TRIANGLE_STRIP):
        {
            const GLuint *iptr = indices;
            for (GLsizei i=2; i<count; ++i,++iptr)
            {
                if ((i%2)) this->operator()(mVertexArrayPtr[*(iptr)], mVertexArrayPtr[*(iptr+2)], mVertexArrayPtr[*(iptr+1)]);
                else this->operator()(mVertexArrayPtr[*(iptr)], mVertexArrayPtr[*(iptr+1)], mVertexArrayPtr[*(iptr+2)]);
            }
            break;
        }
        case (GL_QUADS):
        {
            const GLuint *iptr = indices;
            for (GLsizei i=3; i<count; i+=4,iptr+=4)
            {
                this->operator()(mVertexArrayPtr[*(iptr)], mVertexArrayPtr[*(iptr+1)], mVertexArrayPtr[*(iptr+2)]);
                this->operator()(mVertexArrayPtr[*(iptr)], mVertexArrayPtr[*(iptr+2)], mVertexArrayPtr[*(iptr+3)]);
            }
            break;
        }
        case (GL_QUAD_STRIP):
        {
            const GLuint *iptr = indices;
            for (GLsizei i=3; i<count; i+=2,iptr+=2)
            {
                this->operator()(mVertexArrayPtr[*(iptr)], mVertexArrayPtr[*(iptr+1)], mVertexArrayPtr[*(iptr+2)]);
                this->operator()(mVertexArrayPtr[*(iptr+1)], mVertexArrayPtr[*(iptr+3)], mVertexArrayPtr[*(iptr+2)]);
            }
            break;
        }
        case (GL_POLYGON): //! treat polygons as GL_TRIANGLE_FAN
        case (GL_TRIANGLE_FAN):
        {
            const GLuint *iptr = indices;
            const QVector3D &vfirst = mVertexArrayPtr[*iptr];
            ++iptr;
            for (GLsizei i=2; i<count; ++i,++iptr)
            {
                this->operator()(vfirst, mVertexArrayPtr[*(iptr)], mVertexArrayPtr[*(iptr+1)]);
            }
            break;
        }
        case(GL_POINTS):
        case(GL_LINES):
        case(GL_LINE_STRIP):
        case(GL_LINE_LOOP):
        default:
            //! can not be converted into to triangles.
            break;
        }
    }

private:
    unsigned int mVertexArraySize;
    const QVector3D* mVertexArrayPtr;
};

#endif // UNIZPRIMITIVEFUNCTOR_H
