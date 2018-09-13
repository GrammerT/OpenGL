#ifndef GLAREA_H
#define GLAREA_H
#include "QOpenGLWidget"

class MultiViewer_Container;

class GLArea :public QOpenGLWidget
{
    Q_OBJECT
public:
    GLArea(QWidget *parent,MultiViewer_Container *mvcont);
    ~GLArea();

    void initializeGL();
    void paintEvent(QPaintEvent *e);
    void keyReleaseEvent ( QKeyEvent * e );
    void keyPressEvent ( QKeyEvent * e );
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent ( QMouseEvent * event ) ;
    void wheelEvent(QWheelEvent*e);
    void tabletEvent(QTabletEvent *e);
    void hideEvent(QHideEvent * event);
public:
    int getId(){
        return id;
    }
    //MultiViewer_Container *mvc()
    MultiViewer_Container * mvc()
    {
        return parentmultiview;
    }
private:
    int id;  //the very important unique id of each subwindow.
    MultiViewer_Container* parentmultiview;
};

#endif // GLAREA_H
