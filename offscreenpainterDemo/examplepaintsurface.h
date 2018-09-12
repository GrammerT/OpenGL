#ifndef EXAMPLEPAINTSURFACE_H
#define EXAMPLEPAINTSURFACE_H
#include "opengloffscreensurface.h"

class ExamplePaintSurface : public OpenglOffscreenSurface
{
public:
    ExamplePaintSurface(QScreen *targetScreen=NULL,const QSize& size = QSize(1,1));
    virtual ~ExamplePaintSurface();

protected:
    virtual void initializeGL() override;

    virtual void resizeGL(
            int width,
            int height) override;

    virtual void paintGL() override;

};

#endif // EXAMPLEPAINTSURFACE_H
