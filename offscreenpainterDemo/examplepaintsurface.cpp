#include "examplepaintsurface.h"

ExamplePaintSurface::ExamplePaintSurface(QScreen *targetScreen, const QSize &size)
    :OpenglOffscreenSurface(targetScreen,size)
{

}

ExamplePaintSurface::~ExamplePaintSurface()
{

}

void ExamplePaintSurface::initializeGL()
{

}

void ExamplePaintSurface::resizeGL(int width, int height)
{

}

void ExamplePaintSurface::paintGL()
{
    functions()->glClearColor(1.0,0.0,0.0,1.0);
    functions()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
